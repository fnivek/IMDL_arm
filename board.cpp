#include "board.h"

board::board():
	usb_()
{

}

// initialization code necessary to use the serial port
void board::init()
{
	// Do nothing for now
	usb_.init();
}

// read a byte from the serial port. -1 = failure
int board::read()
{
	return usb_.read();
}

// write data to the connection to ROS
void board::write(uint8_t* data, int length)
{
	usb_.write(data, length);
}

// returns milliseconds since start of program
unsigned long board::time()
{
	return 0;
}

// Updates the hardware
void board::hardwareUpdate()
{
	usb_.poll();
}