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

int main(void)
{

	rcc_clock_setup_hse_3v3(&hse_8mhz_3v3[CLOCK_3V3_120MHZ]);

	usb usb_interface;
	usb_interface.init_usb();

	// Blink LEDs to let us know everythings okay
	rcc_periph_clock_enable(RCC_GPIOD);
	gpio_mode_setup(GPIOD, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO12 | GPIO13 | GPIO14 | GPIO15);


	int i;
	while (1) {
		usb_interface.poll();

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
