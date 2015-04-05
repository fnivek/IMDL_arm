#include "HC-SR04_Array.h"

hc_sr04_array::hc_sr04_array():
	fr_trig_(GPIOC, GPIO1), fr_echo_(GPIOC, GPIO0),
	fl_trig_(GPIOA, GPIO1), fl_echo_(GPIOA, GPIO0),
	f_trig_(GPIOB, GPIO1), 	f_echo_(GPIOB, GPIO0),
	b_trig_(GPIOD, GPIO1), 	b_echo_(GPIOD, GPIO0)

{

	/* Setup GPIO
	// Enable gpio clock
	rcc_periph_clock_enable(RCC_GPIOC);

	// Set GPIO mode
	gpio_mode_setup(sig_.port, GPIO_MODE_INPUT, GPIO_PUPD_NONE, sig_.number);

	// Initilize to cleared
	gpio_clear(sig_.port, sig_.number);

	// Setup timer
	// Step 1 enable peripherial clock
	rcc_periph_clock_enable(RCC_TIM2);

	// Step 2 reset peripherial:
	timer_reset(TIM2);

	// Step 3 set mode div 1 since 32 bits wide, count up, 
	timer_set_mode(TIM2, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE,
               TIM_CR1_DIR_UP);

	// Step 4 set the period to max
	timer_set_period(TIM2, 0xFFFFFFFF);

	// Step 5 Disable outputs
	timer_disable_oc_output(TIM2, TIM_OC1);
	timer_disable_oc_output(TIM2, TIM_OC2);
	timer_disable_oc_output(TIM2, TIM_OC3);
	timer_disable_oc_output(TIM2, TIM_OC4);

	// Reset timer
	timer_set_counter(TIM2, 0);

	// Step 5 enable the timer
	timer_enable_counter(TIM2);

	// Step 6 enable timer 2 interrupts
	nvic_enable_irq(NVIC_TIM2_IRQ);
*/
}

hc_sr04_array::~hc_sr04_array()
{

}

hc_sr04_array* hc_sr04_array::get_instance()
{
	if(hc_sr04_array::single_ == 0)
	{
		hc_sr04_array::single_ = new hc_sr04_array();
	}

	return hc_sr04_array::single_;
}

hc_sr04_array* hc_sr04_array::single_ = 0;