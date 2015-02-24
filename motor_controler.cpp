#include "motor_controler.h"

motor_controler::motor_controler(uint32_t timer)
{
// Enable peripherials
	// timer
	switch(timer)
	{

	case TIM2:
		rcc_periph_clock_enable(RCC_TIM2);
		break;

	case TIM3:
		rcc_periph_clock_enable(RCC_TIM3);
		break;
		
	case TIM4:
		rcc_periph_clock_enable(RCC_TIM4);
		break;
		
	case TIM5:
		rcc_periph_clock_enable(RCC_TIM5);
		break;
		
	case TIM6:
		rcc_periph_clock_enable(RCC_TIM6);
		break;
		
	case TIM7:
		rcc_periph_clock_enable(RCC_TIM7);
		break;
		
	case TIM12:
		rcc_periph_clock_enable(RCC_TIM12);
		break;
		
	case TIM13:
		rcc_periph_clock_enable(RCC_TIM13);
		break;
		
	case TIM14:
		rcc_periph_clock_enable(RCC_TIM14);
		break;
	}

	// GPIO


// Setup timer
	// Step 1 reset peripherial:
	timer_reset(timer);

	// Step 2 set mode to 
	timer_set_mode(timer, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_CENTER_1,
               TIM_CR1_DIR_UP);

	// Step 3 set output compare to PWM
	timer_set_oc_mode(timer, TIM_OC1, TIM_OCM_PWM2);

	// Step 4 enable output compare
	timer_enable_oc_output(timer, TIM_OC1);

	// Step 5 set the compare value
	timer_set_oc_value(timer, TIM_OC1, 200);

	// Step 6 set the period
	timer_set_period(timer, 1000);

	// Step 7 enable the timer
	timer_enable_counter(timer);

}