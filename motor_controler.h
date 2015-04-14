/*
 *
 *		This node is the header for a motor controller class
 *
 *			This class uses timer one for PWM generation
 *			Controls both motors
 *			Theory of opperation: 
 *				* IN 1 and IN 2 control direction by setting them to opposite values
 *				* PWM controls the speed of the motor
 *
 */

 // TODO figure out how to get encoders working

 #ifndef MOTOR_CONTROLER_H
 #define MOTOR_CONTROLER_H

 //Std includes
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>

 //My includes
 #include "helpers.h"

// TODO: find where this actually comes from
#define NULL 0

class motor_controler
{
private:	// Enums
	enum pin_number
	{
		LEFT_IN1,
		LEFT_IN2,
		LEFT_PWM,
		RIGHT_IN1,
		RIGHT_IN2,
		RIGHT_PWM,
		NUMBER_OF_PINS
	};

public:		// Enums
	enum direction
	{
		FREE_SPIN_H,
		FREE_SPIN_L,
		FORWARD,
		REVERSE
	};

private:	// Vars
	pin pins_[NUMBER_OF_PINS];

	// Set to 20 KHz
	// ticks = (120MHz / 2) / 20 KHz  
	const uint32_t pwm_ticks = 3000;	

	static motor_controler* single_;

	uint16_t left_pos_, right_pos_;

private:	// Functions
	motor_controler();

	// Do not implement!
	motor_controler(motor_controler const&){};
	void operator=(motor_controler const&){};

	~motor_controler();

public:		// Functions
	// Get the only instance of motor controller
	static motor_controler* get_instance();

	void setLeftDir_(direction dir);
	void setRightDir_(direction dir);

	// Percent is 0 to 1
	void setLeftDuty_(float percent);
	void setRightDuty_(float percent);

	// Update the PD controlers
	void update_();

	uint16_t getLeftPos_();
	uint16_t getRightPos_();

	void stop_();


};

 #endif