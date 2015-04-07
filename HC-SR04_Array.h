#ifndef HC_SR04_ARRAY_H
#define HC_SR04_ARRAY_H

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/exti.h>
#include <libopencm3/stm32/timer.h>
#include <libopencm3/cm3/nvic.h>

#include "helpers.h"


/*
 *			HC-SR04 array
 *	This class implements four HC-SR04 ultrasonic sensors
 *		It uses 8 pins (defined in main.cpp) and TIM2
 *		TIM2 is used to generate a 10 us pulse for the triger pins
 *		TIM2 is also used to measure the pulse width of the echo signals
 *		Uses system mills to change between sonars
 *	Control flow:
 *		while true
 *			Triger sonar[i]
 *			Wait for return or timeout
 *				if return succeded set distance
 *			On timeout
 *				if no return set distance to max
 *				++i
 *				Wrap(i)
 */

class hc_sr04_array
{
private:	// Enumerators
	enum interface_id
	{
		IFACE_F,
		IFACE_B,
		IFACE_FR,
		IFACE_FL,
		NUM_INTERFACES
	};



private:	// Structs
	typedef struct interface
	{
		pin trig_;
		pin echo_;

		interface(uint32_t trig_port, uint16_t trig_number,
				  uint32_t echo_port, uint16_t echo_number):
			trig_(trig_port, trig_number),
			echo_(echo_port, echo_number)
		{
		}

		interface():
			trig_(0, 0),
			echo_(0, 0)
		{
		}
	} interface;

private:	// Consts
	static const uint32_t TRIG_PULSE_WIDTH;
	static const uint16_t TICKS_PER_IFACE;

private: 	//Vars
	static hc_sr04_array* single_;

	uint8_t current_interface_;

	// All pins
	interface interfaces_[NUM_INTERFACES];

	// Distances
	uint32_t distance_ticks_[NUM_INTERFACES];

	// system tic count
	uint16_t current_ticks_;

	// Did the last sonar return a value
	bool successful_read_;

	// Did we already stop the pulse
	bool stoped_pulse_;
	
private:	// functions

	hc_sr04_array();

	// Do not implement!
	hc_sr04_array(hc_sr04_array const&){};
	void operator=(hc_sr04_array const&){};

	~hc_sr04_array();

public:		// Functions
	static hc_sr04_array* get_instance();

	void pulseTimerISR();

	void systemTimerISR();

	void extiISR(uint32_t caller_id);
};

// None class funcitons
//void tim2_isr(void);
//void exti0_isr(void);
//void exti1_isr(void);
//void exti2_isr(void);
//void exti3_isr(void);

#endif