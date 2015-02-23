/*
 *  This file is the firmware that controls the hardware interface for
 *    Kip C Droid
 */

// Library includes
#include <stdlib.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/usb/usbd.h>
#include <libopencm3/usb/cdc.h>
#include <libopencm3/cm3/scb.h>

// User defined includes
#include "usb.h"

int main(void)
{


  //usb usb_interface;
  //usb_interface.init_usb();
  const char * usb_strings[] = {"KipCDroid", "HardwareInterface"};
  /* Buffer to be used for control requests. */
  uint8_t usbd_control_buffer[128];

  usbd_device *usbd_dev;

	rcc_clock_setup_hse_3v3(&hse_8mhz_3v3[CLOCK_3V3_120MHZ]);

	rcc_periph_clock_enable(RCC_GPIOA);
	rcc_periph_clock_enable(RCC_OTGFS);

	gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE,
			GPIO9 | GPIO11 | GPIO12);
	gpio_set_af(GPIOA, GPIO_AF10, GPIO9 | GPIO11 | GPIO12);

	usbd_dev = usbd_init(&otgfs_usb_driver, &dev, &config,
			usb_strings, 2,
			usbd_control_buffer, sizeof(usbd_control_buffer));

	usbd_register_set_config_callback(usbd_dev, cdcacm_set_config);

  int i;
  while (1) {
	  //usb_interface.poll();
	  usbd_poll(usbd_dev);

    /*gpio_toggle(GPIOD, GPIO12);
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
    */
  }
}
