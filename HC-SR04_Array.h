#ifndef HC_SR04_ARRAY_H
#define HC_SR04_ARRAY_H

#include <libopencm3/stm32/gpio.h>

class hc_sr04_array
{
private: 	//Vars
	static hc_sr04_array* single_;
	
private:	// functions

	hc_sr04_array();

	// Do not implement!
	hc_sr04_array(hc_sr04_array const&){};
	void operator=(hc_sr04_array const&){};

	~hc_sr04_array();

public:		// Functions
	static hc_sr04_array* get_instance();
};

#endif