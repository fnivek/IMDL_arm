/*
 *  This file is the firmware that controls the hardware interface for
 *    Kip C Droid
 *
 *	Pin out
 *		Pin 			  Direction			Conection					Use
 * -----------------------------------------------------------------------------
 *		PC10				-->				Motor 1 in 1 			Direction control
 *		PA15				-->				Motor 1 in 2 			Direction control
 *		PA8					-->				Motor 1 PWM				Motor speed control (PWM)
 *		PC11				-->				Motor 2 in 1 			Direction control
 *		PC12				-->				Motor 2 in 2			Direction control
 *		PA10				-->				Motor 2 PWM				Motor speed control (PWM)
 *
 *		PA11				<-->			USB DM					USB data -
 *		PA12				<-->			USB DP					USB data +
 *		PA9					 pwr 			VBUS					USB VBUS
 *
 *		PC?					<-->			ping))) Signal			distance measurment
 *
 *		PA13				?				Programer				Programing don't mess with this!
 *		PA14				?				Programer				Programing don't mess with this!
 *
 *		PD[12..15]			-->				Status LEDs				Show the status of the robot
 *
 *		PC15				<-->			Ping Signal				EXTI15 for PING)))				
 *		
 */

/*
 *	Timer			who				why					config
 * --------------------------------------------------------------------
 * TIM1			   M1, M2		PWM generation		20KHz, DIV 1, OC
 * TIM2				Ping 		delays				
 */

// Library includes
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/usb/usbd.h>
#include <libopencm3/usb/cdc.h>
#include <libopencm3/cm3/scb.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/cm3/systick.h>

// User defined includes
#include "usb.h"
#include "motor_controler.h"
#include "helpers.h"
#include "ping.h"
#include "board.h"

 #define MAX_SPEED 0.70

/* monotonically increasing number of milliseconds from reset
 * overflows every 49 days if you're wondering
 */
volatile uint32_t system_millis = 0;

/* Called when systick fires */
void sys_tick_handler(void)
{
	system_millis++;
}

/* sleep for delay milliseconds */
static void msleep(uint32_t delay)
{
	uint32_t wake = system_millis + delay;
	while (wake > system_millis);
}

/* Set up a timer to create 1mS ticks. */
static void systick_setup(void)
{
	/* clock rate / 1000 to get 1mS interrupt rate */
	systick_set_reload(120000);
	systick_set_clocksource(STK_CSR_CLKSOURCE_AHB);
	systick_counter_enable();
	/* this done last */
	systick_interrupt_enable();
}

void simple_obstical_avoidance();


ping pingy({GPIOC, GPIO15});
// Initilize motor controller
pin m1_in1 = {GPIOC, GPIO10};
pin m1_in2 = {GPIOA, GPIO15};
pin m1_pwm = {GPIOA, GPIO8};
pin m2_in1 = {GPIOC, GPIO11};
pin m2_in2 = {GPIOC, GPIO12};
pin m2_pwm = {GPIOA, GPIO10};
motor_controler motors(m1_in1, m1_in2, m1_pwm,
					   m2_in1, m2_in2, m2_pwm);

int main(void)
{
	board bd;
	bd.init();

	systick_setup();
	/* Initilize the clock to: 
		.pllm = 25,
		.plln = 240,
		.pllp = 2,
		.pllq = 5,
		.hpre = RCC_CFGR_HPRE_DIV_NONE,
		.ppre1 = RCC_CFGR_PPRE_DIV_4,
		.ppre2 = RCC_CFGR_PPRE_DIV_2,
		.power_save = 1,
		.flash_config = FLASH_ACR_ICE | FLASH_ACR_DCE |
			FLASH_ACR_LATENCY_3WS,
		.apb1_frequency = 30000000,
		.apb2_frequency = 60000000,
  	*/
	rcc_clock_setup_hse_3v3(&hse_8mhz_3v3[CLOCK_3V3_120MHZ]);

	// Initilize USB interface
	usb usb_interface;			// Note uses PA 9 11 and 12
	usb_interface.init_usb();
	
	motors.init();
	motor_controler::direction current_dir = motor_controler::FORWARD;
	motors.set_m1_dir(current_dir);
	motors.set_m2_dir(current_dir);

	// Initilize Ping ultrasonic sensor
	//pingy.init();

	// Blink LEDs to let us know everythings okay
	rcc_periph_clock_enable(RCC_GPIOD);
	gpio_mode_setup(GPIOD, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO12 | GPIO13 | GPIO14 | GPIO15);



	int i;
	while (1) {
		// TODO: move to an interrupt
		usb_interface.poll();

		//simple_obstical_avoidance();
	}
}

void tim2_isr(void)
{
	pingy.timer_isr();
}

void turn_right()
{
	motors.set_m2_dir(motor_controler::REVERSE);
	motors.set_m1_dir(motor_controler::FORWARD);
	motors.set_m1_duty(MAX_SPEED);
	motors.set_m2_duty(MAX_SPEED);
}

void turn_left()
{
	motors.set_m1_dir(motor_controler::REVERSE);
	motors.set_m2_dir(motor_controler::FORWARD);
	motors.set_m1_duty(MAX_SPEED);
	motors.set_m2_duty(MAX_SPEED);
}

void stop()
{
	motors.set_m1_dir(motor_controler::FREE_SPIN_H);
	motors.set_m2_dir(motor_controler::FREE_SPIN_H);
	motors.set_m1_duty(0);
	motors.set_m2_duty(0);
}

void forward()
{
	motors.set_m1_dir(motor_controler::FORWARD);
	motors.set_m2_dir(motor_controler::FORWARD);
	motors.set_m1_duty(MAX_SPEED);
	motors.set_m2_duty(MAX_SPEED);
}

void simple_obstical_avoidance()
{
	gpio_clear(GPIOD, GPIO12 |GPIO13 | GPIO14 | GPIO15);

	// Go forward till we find something
	forward();
	while(pingy.get_distance() > 80);

	gpio_set(GPIOD, GPIO12);

	// Turn left
	volatile uint32_t debug = timer_get_counter(TIM1);
	if((debug >> 1) & 0x1)
	{
		turn_left();
	}
	else
	{
		turn_right();
	}

	while(pingy.get_distance() < 120);

	gpio_set(GPIOD, GPIO13);

	switch((timer_get_counter(TIM1) >> 1) & 0x3)
	{
	case 0:
		msleep(100);
	case 1:
		msleep(100);
	case 2:
		msleep(100);
	case 3:
		msleep(100);
	defualt:
		msleep(100);
	}

}
