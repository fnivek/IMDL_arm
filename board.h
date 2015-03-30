#ifndef BOARD_H
#define BOARD_H

//#include <stdlib.h>
#include <libopencm3/stm32/gpio.h>
#include "usb.h"
#include <libopencm3/cm3/systick.h>

class board
{
private:
	usb usb_;

	/* monotonically increasing number of milliseconds from reset
	 * overflows every 49 days if you're wondering
	 */
	static volatile uint32_t system_millis;

	/* Called when systick fires */
	static void sys_tick_handler(void);

	/* Set up a timer to create 1mS ticks. */
	static void systick_setup(void);

public:
  board();

  // initialization code necessary to use the serial port
  void init(); 

  // read a byte from the serial port. -1 = failure
  int read();

  // write data to the connection to ROS
  void write(uint8_t* data, int length);

  // returns milliseconds since start of program
  unsigned long time();

  void hardwareUpdate();

};

#endif