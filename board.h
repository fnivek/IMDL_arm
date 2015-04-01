#ifndef BOARD_H
#define BOARD_H

//#include <stdlib.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/cm3/nvic.h>		// Required to override syst tick callback

#include "usb.h"

class board
{
private:
	usb usb_;

	/* Called when systick fires */
	//static void sys_tick_handler(void);

	/* Set up a timer to create 1mS ticks. */
	static void systick_setup_(void);

	uint32_t last_time_;

public:
	/* monotonically increasing number of milliseconds from reset
	 * overflows every 49 days if you're wondering
	 */
	static volatile uint32_t system_millis_;

public:
  board();

  // initialization code necessary to use the serial port
  void init_(); 

  // write data to the connection to ROS
  void write_(uint8_t* data, int length);

  // Data read callback
  //friend void read_cb_(char* buf, uint8_t len);

  // returns milliseconds since start of program
  unsigned long time_();

  void hardwareUpdate_();

};

#endif