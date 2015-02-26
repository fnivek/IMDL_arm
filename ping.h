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
		US_5 =			5,
		US_200 =		200,
	};

private:
	pin sig_;

private:
	// Send out a pulse
	void send_pulse();

	// Interrupt service routine for falling edge pulse
	//	This will read in the value of 
	void recieve_pulse_isr();

	// Interrupt service routine for timer oc
	//	used when the system must wait i.e. after a pulse is measured we 
	//	must wait 200 us before next read
	void wait_isr();

public:
	// Constructor
	ping(pin sig);

	//Get latest reading 
	float get_distance();

	// Get time since last reading in us
	float get_time_since_read();


};

#endif