#ifndef BOARD_H
#define BOARD_H

//#include <stdlib.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/cm3/nvic.h>		// Required to override syst tick callback
#include <string.h>

#include "usb.h"
#include "helpers.h"
#include "HC-SR04_Array.h"
#include "motor_controler.h"

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
		MISSED_HEARTBEAT,
		IDK_5,
		IDK_6,
	};

private:	// Vars
	usb* usb_;

	pin heartbeat_led_, orange_led_, red_led_, blue_led_; 

	hc_sr04_array* sonars_;

	motor_controler* motors_;

	bool recieved_comm_heartbeat_;
	bool missed_heartbeat_;

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
	volatile uint32_t system_millis_;

	// Identifiers
	static const char left_duty_id_[];
	static const char right_duty_id_[];
	static const char heartbeat_id_[];

public:		// Functions
	// Get the only instance of board
	static board* get_instance();

	// write data to USB
	void write_(uint8_t* data, int length);

	void setStatus_(status_ status);

	// Toggle the heart beat led
	void beat_();

	// Updates as often as possible
	//		Contains USB poll
	void hardwareUpdate_();

	// Update at 0.5 Hz
	//		Contains communication heat beat
	void updateHalfHz_();

	// 1 Hz update function
	//		Contains board heart beat
	void update1hz_();

	// 10 Hz update function
	//		Contains sonar out, and motor pos out
	void update10hz_();

	// 1000 Hz update function
	//		Contains sonar update
	void update1000hz_();

public:		// Friend functions
	friend void read_cb_(char* buf, uint16_t len);
	friend void sys_tick_handler(void);

};

// None class functions
// Increments system ticks
//void sys_tick_handler(void);			// This is also defined as a weak symbol in libopencm3/cm3/nvic.h

// Call back for read functions
void read_cb_(char* buf, uint16_t len);

#endif