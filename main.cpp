/*
 *  This file is the firmware that controls the hardware interface for
 *    Kip C Droid
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
	usb* usb_interface = usb::get_instance();
	usb_interface->init_usb();

	// Initilize motor controllers
	motor_controler left_motor(TIM2);
	motor_controler right_motor(TIM3);

	// Blink LEDs to let us know everythings okay
	rcc_periph_clock_enable(RCC_GPIOD);
	gpio_mode_setup(GPIOD, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO12 | GPIO13 | GPIO14 | GPIO15);


	int i;
	while (1) {
		usb_interface->poll();

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
