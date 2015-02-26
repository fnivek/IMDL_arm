#ifndef ULTRA_SONIC_SENSOR_H
#define ULTRA_SONIC_SENSOR_H

/*
 * Class for the ping ultrasonic sensor
 */
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/exti.h>
#include <libopencm3/stm32/timer.h>
#include <libopencm3/cm3/nvic.h>

#include "helpers.h"

 //TODO: Set up to use any acceptable pin

class ping
{
private:
	// Enumerator to keep track of how many ticks to wait
	enum ticks
	{
		US_5 =			300,
		US_10 =			600,
		US_200 =		1200,
		US_750 = 		45000,
		US_18500 =		1110000,
		US_19250 =		1155000,
		S_1 =			60000000,
		S_10 =			600000000

	};

	// Enumerator to help track the current stage in the ping protocol
	enum stage
	{
		SEND_PULSE,
		STOP_PULSE,
		GRAB_RESULT,
		WAIT_FOR_NEXT,
	};

private:
	// GPIO pin used for the signal of the PING)))
	pin sig_;

	stage stage_; 

	float distance_;

private:
	// Send out a pulse
	void send_pulse();

	// Stop the pulse
	void stop_pulse();

	// Grab result
	void grab_result();

	// Wait for next
	void wait_for_next();

public:
	// Constructor
	ping(pin sig);

	// Initilize
	void init();

	//Get latest reading 
	float get_distance();

	// Get time since last reading in us
	float get_time_since_read();

	// Interrupt service routine for timer interrupts edge pulse
	//	This will read in the value of 
	//	used when the system must wait i.e. after a pulse is measured we 
	//	must wait 200 us before next read
	void timer_isr();


};

#endif