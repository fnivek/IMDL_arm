#include "ping.h"

// Send out a pulse
void ping::send_pulse()
{

}

// Interrupt service routine for falling edge pulse
//	This will read in the value of 
void ping::recieve_pulse_isr()
{

}

// Interrupt service routine for timer oc
//	used when the system must wait i.e. after a pulse is measured we 
//	must wait 200 us before next read
void ping::wait_isr()
{

}

// Constructor
ping::ping(pin sig)
{
	// EXTIx exist only on pins 0, 1 and 15
	sig_ = {GPIOC, GPIO15};
}


//Get latest reading 
float ping::get_distance()
{
	return 0;
}

// Get time since last reading in us
float ping::get_time_since_read()
{
	return 0;
}
