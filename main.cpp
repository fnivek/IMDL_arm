/*
 *  This file is the firmware that controls the hardware interface for
 *    Kip C Droid
 *
 *	Pin out
 *		Pin 			  Direction			Conection					Use
 * -----------------------------------------------------------------------------
 *		PA13				-->				Motor 1 in 1 			Direction control
 *		PA15				-->				Motor 1 in 2 			Direction control
 *		PA8					-->				Motor 1 PWM				Motor speed control (PWM)
 *		PC11				-->				Motor 2 in 1 			Direction control
 *		PA14				-->				Motor 2 in 2			Direction control
 *		PA10				-->				Motor 2 PWM				Motor speed control (PWM)
 *
 *		PA11				<-->			USB DM					USB data -
 *		PA12				<-->			USB DP					USB data +
 *		PA9					 pwr 			VBUS					USB VBUS
 *
 *							<-->			ping))) Signal			distance measurment		
 */

// Library includes
//#include <stdlib.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/usb/usbd.h>
#include <libopencm3/usb/cdc.h>
#include <libopencm3/cm3/scb.h>

// User defined includes
#include "usb.h"
#include "motor_controler.h"
 #include "helpers.h"

int main(void)
{

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

	// Initilize motor controller
	pin m1_in1 = {GPIOA, GPIO13};
	pin m1_in2 = {GPIOA, GPIO15};
	pin m1_pwm = {GPIOA, GPIO8};
	pin m2_in1 = {GPIOC, GPIO11};
	pin m2_in2 = {GPIOA, GPIO14};
	pin m2_pwm = {GPIOA, GPIO10};
	motor_controler motors(m1_in1, m1_in2, m1_pwm,
						   m2_in1, m2_in2, m2_pwm);
	motors.init();
	motors.set_m1_dir(motor_controler::FORWARD);

	// Blink LEDs to let us know everythings okay
	rcc_periph_clock_enable(RCC_GPIOD);
	gpio_mode_setup(GPIOD, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO12 | GPIO13 | GPIO14 | GPIO15);


	int i;
	while (1) {
		usb_interface.poll();

		//motors.set_m1_dir(motor_controler::FORWARD);

		gpio_toggle(GPIOD, GPIO12);
		for(i = 0; i < 0xFF; i++)
		{
		  __asm__("nop");
		}
		gpio_toggle(GPIOD, GPIO13);
		for(i = 0; i < 0xFF; i++)
		{
		  __asm__("nop");
		}

		//motors.set_m1_dir(motor_controler::REVERSE);

		gpio_toggle(GPIOD, GPIO14);
		for(i = 0; i < 0xFF; i++)
		{
		  __asm__("nop");
		}
		gpio_toggle(GPIOD, GPIO15);
		for(i = 0; i < 0xFF; i++)
		{
		  __asm__("nop");
		}
	}
}
