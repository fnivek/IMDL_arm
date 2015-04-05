#ifndef BOARD_H
#define BOARD_H

//#include <stdlib.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/cm3/nvic.h>		// Required to override syst tick callback

#include "usb.h"
#include "helpers.h"
#include "HC-SR04_Array.h"

class board
{
public:		// Enumerators
	enum status_
	{
		OK,
		IDK_1,
		ERROR,
		IDK_2,
		IDK_3,
		IDK_4,
		IDK_5,
		IDK_6,
	};

private:	// Vars
	usb* usb_;

	uint32_t last_time_;

	pin heartbeat_led_, orange_led_, red_led_, blue_led_; 

	hc_sr04_array* sonics_;

private:	// Functions
	/* Called when systick fires */
	//static void sys_tick_handler(void);

	/* Set up a timer to create 1mS ticks. */
	static void systick_setup_(void);

	static board* single_;

	board();

	// Do not implement!
	board(board const&){};
	void operator=(board const&){};

	~board();

public:		//Vars
	/* monotonically increasing number of milliseconds from reset
	 * overflows every 49 days if you're wondering
	 */
	static volatile uint32_t system_millis_;

public:		// Functions
	// Get the only instance of board
	static board* get_instance();

	// initialization code necessary to use the serial port
	void init_(); 

	// write data to the connection to ROS
	void write_(uint8_t* data, int length);

	// returns milliseconds since start of program
	unsigned long time_();

	void hardwareUpdate_();

	void setStatus_(status_ status);

	// Toggle the heart beat led
	void beat_();

};

// None class functions
// Increments system ticks
void sys_tick_handler(void);			// This is also defined as a weak symbol in libopencm3/cm3/nvic.h

// Call back for read functions
void read_cb_(void* buf, uint16_t len);

#endif