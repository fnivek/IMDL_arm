/*
 *  This file is the firmware that controls the hardware interface for
 *    Kip C Droid
 *
 *	Pin out
 *		Pin 			  Direction			Conection					Use
 * -----------------------------------------------------------------------------
 *		PC10				-->				Motor 1 in 1 			Direction control
 *		PA15				-->				Motor 1 in 2 			Direction control
 *		PA8					-->				Motor 1 PWM				Motor speed control (PWM)
 *		PC11				-->				Motor 2 in 1 			Direction control
 *		PC12				-->				Motor 2 in 2			Direction control
 *		PA10				-->				Motor 2 PWM				Motor speed control (PWM)
 *
 *		PA11				<-->			USB DM					USB data -
 *		PA12				<-->			USB DP					USB data +
 *		PA9					 pwr 			VBUS					USB VBUS
 *
 *		PC?					<-->			ping))) Signal			distance measurment
 *
 *		PA13				?				Programer				Programing don't mess with this!
 *		PA14				?				Programer				Programing don't mess with this!
 *
 *		PD[12..15]			-->				Status LEDs				Show the status of the robot
 *
 *		PB0					<--				F sonar echo 			EXTI0 for Front middle sonar
 *		PB1					<--				B sonar echo			EXTI0 for Back sonar			
 *		PB2 				<--				FR sonar echo 			EXTI0 for Front right sonar
 *		PB3					<--				FL sonar echo			EXTI0 for Front left sonar	
 *		PA0 				-->				F sonar Trig.			Trigger for Front middle sonar
 *		PA1 				-->				B sonar Trig.			Trigger for back sonar
 *		PA2 				-->				FR sonar Trig.			Trigger for Front right sonar
 *		PA3 				-->				FL sonar Trig.			Trigger for Front left sonar
 * 
 */

/*
 *	Timer			who				why					config
 * --------------------------------------------------------------------
 * TIM1			   M1, M2		PWM generation		20KHz, DIV 1, OC
 * TIM2			  HC_SR04s 		Input capture						
 */

// Library includes
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/usb/usbd.h>
#include <libopencm3/usb/cdc.h>
#include <libopencm3/cm3/scb.h>

// User defined includes
#include "usb.h"
#include "motor_controler.h"
#include "helpers.h"
#include "board.h"

 #define MAX_SPEED 0.70

// make c++ happy
 void *__dso_handle;
 
int __cxa_atexit(void (*destructor) (void *), void *arg, void *dso);
void __cxa_finalize(void *f);

int main(void)
{

	board* bd = board::get_instance();

	while (1) {
		bd->hardwareUpdate_();

		//simple_obstical_avoidance();
	}
}