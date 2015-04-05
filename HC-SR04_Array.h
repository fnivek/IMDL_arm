#ifndef HC_SR04_ARRAY_H
#define HC_SR04_ARRAY_H

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/exti.h>
#include <libopencm3/stm32/timer.h>
#include <libopencm3/cm3/nvic.h>

#include "helpers.h"

class hc_sr04_array
{
private: 	//Vars
	static hc_sr04_array* single_;

	// All pins
	pin fr_trig_, 	fr_echo_;
	pin fl_trig_, 	fl_echo_;
	pin f_trig_,	f_echo_;
	pin b_trig_, 	b_echo_;
	
private:	// functions

	hc_sr04_array();

	// Do not implement!
	hc_sr04_array(hc_sr04_array const&){};
	void operator=(hc_sr04_array const&){};

	~hc_sr04_array();

public:		// Functions
	static hc_sr04_array* get_instance();
};

// None class funcitons


#endif