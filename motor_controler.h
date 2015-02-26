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

 #ifndef MOTOR_CONTROLER_H
 #define MOTOR_CONTROLER_H

 //Std includes
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>

 //My includes
 #include "helpers.h"

class motor_controler
{
private:
	enum pin_number
	{
		M1_IN1,
		M1_IN2,
		M1_PWM,
		M2_IN1,
		M2_IN2,
		M2_PWM,
		NUMBER_OF_PINS
	};

public:
	enum direction
	{
		FREE_SPIN_H,
		FREE_SPIN_L,
		FORWARD,
		REVERSE
	};

private:
	pin pins_[NUMBER_OF_PINS];

	// Set to 20 KHz
	// ticks = (120MHz / 2) / 20 KHz  
	const uint32_t pwm_ticks = 3000;		

public:
	motor_controler(pin m1_in1, pin m1_in2, pin m1_pwm,
					pin m2_in1, pin m2_in2, pin m2_pwm);

	void init();

	void set_m1_dir(direction dir);
	void set_m2_dir(direction dir);

	// Percent is 0 to 1
	void set_m1_duty(float percent);
	void set_m2_duty(float percent);


};

 #endif