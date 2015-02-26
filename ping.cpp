#include "ping.h"

// Send out a pulse
//		This is the initial pulse of the ping sensor protocol
//			Set GPIO to output
//			set GPIO to high
//			Reset timer
//			Set oc value
//			Enable timer interrupt

void ping::send_pulse()
{
	// Set GPIO high
	gpio_mode_setup(sig_.port, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, sig_.number);
	gpio_set(sig_.port, sig_.number);

	// Reset timer
	timer_set_counter(TIM2, 0);

	// Set output compare
	timer_set_oc_value(TIM2, TIM_OC1, US_5);

	// Enable interrupts
	timer_enable_irq(TIM2, TIM_DIER_CC1IE);
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
	
	// Setup GPIO
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

	// Step 5 enable the timer
	timer_enable_counter(TIM2);


	// Send first pulse
	send_pulse();

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
