/*
 *
 *		This node is the header for a motor controller class
 *
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

class motor_controler
{
public:
	motor_controler(uint32_t timer);
};

 #endif