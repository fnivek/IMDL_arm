#ifndef BOARD_H
#define BOARD_H

//#include <stdlib.h>
#include <libopencm3/stm32/gpio.h>
#include "usb.h"

class board
{
private:
	usb usb_;

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