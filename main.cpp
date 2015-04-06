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
 *		PB0					<--				F sonar echo 			EXTI0 for Front middle sonar
 *		PB1					<--				B sonar echo			EXTI0 for Back sonar			
 *		PB2 				<--				FR sonar echo 			EXTI0 for Front right sonar
 *		PB3					<--				FL sonar echo			EXTI0 for Front left sonar	
 *		PA0 				-->				F sonar Trig.			Trigger for Front middle sonar
 *		PA1 				-->				B sonar Trig.			Trigger for back sonar
 *		PA2 				-->				FR sonar Trig.			Trigger for Front right sonar
 *		PA3 				-->				FL sonar Trig.			Trigger for Front left sonar
 * 
 */

/*
 *	Timer			who				why					config
 * --------------------------------------------------------------------
 * TIM1			   M1, M2		PWM generation		20KHz, DIV 1, OC
 * TIM2			  HC_SR04s 		Input capture						
 */

// Library includes
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/usb/usbd.h>
#include <libopencm3/usb/cdc.h>
#include <libopencm3/cm3/scb.h>

// User defined includes
#include "usb.h"
#include "motor_controler.h"
#include "helpers.h"
#include "board.h"

 #define MAX_SPEED 0.70

// make c++ happy
 void *__dso_handle;
 
int __cxa_atexit(void (*destructor) (void *), void *arg, void *dso);
void __cxa_finalize(void *f);

// Forward declerations
//void simple_obstical_avoidance();
void forward();
void stop();
void turn_right();
void turn_left();

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

	board* bd = board::get_instance();

	motors.init();
	motor_controler::direction current_dir = motor_controler::FORWARD;
	motors.set_m1_dir(current_dir);
	motors.set_m2_dir(current_dir);

	stop();

	while (1) {
		bd->hardwareUpdate_();

		//simple_obstical_avoidance();
	}
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

/*
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
		//msleep(100);
	case 1:
		//msleep(100);
	case 2:
		//msleep(100);
	case 3:
		//msleep(100);
	defualt:
		//msleep(100);
	}

}
*/