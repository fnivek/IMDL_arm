#include "ping.h"

// Send out a pulse
//		This is the initial pulse of the ping sensor protocol
//			Set GPIO to output
//			set GPIO to high
//			Set oc value
//			Enable timer interrupt

void ping::send_pulse()
{
	timer_set_counter(TIM2, 0);

	// Set next stage
	stage_ = STOP_PULSE;

	// Set GPIO high
	gpio_mode_setup(sig_.port, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, sig_.number);
	gpio_set(sig_.port, sig_.number);

	// Set output compare
	timer_set_oc_value(TIM2, TIM_OC1, US_5);

	// Enable interrupts
	timer_enable_irq(TIM2, TIM_DIER_CC1IE);
}


// Stop the pulse
//	Set timer to input capture
//	Set GPIO to input
void ping::stop_pulse()
{
	timer_set_counter(TIM2, 0);

	// Set next stage
	stage_ = WAIT_FOR_NEXT;

	// Turn off pulse
	gpio_clear(sig_.port, sig_.number);
	timer_set_oc_value(TIM2, TIM_OC1, US_750+50);

	// Set GPIO to input 
	gpio_mode_setup(sig_.port, GPIO_MODE_INPUT, GPIO_PUPD_NONE, sig_.number);
	//exti_select_source(1, sig_.port);
	//exti_set_trigger(1, EXTI_TRIGGER_FALLING);

	// Set input capture for falling edge from TI1
	//timer_ic_set_input(TIM2, TIM_IC1, TIM_IC_IN_TI1);
	//timer_ic_set_polarity(TIM2, TIM_IC1, TIM_IC_FALLING);
	//timer_ic_enable(TIM2, TIM_IC1);

	while(!(gpio_get(sig_.port, sig_.number) & sig_.number));
	while(gpio_get(sig_.port, sig_.number) & sig_.number);

	uint32_t temp = timer_get_counter(TIM2);
	//		(clk  / clksper second) * speed of sound (cm/s)
	distance_ = (temp / 60e6) * 34029.0;

	

}

// Grab result
void ping::grab_result()
{

	// Set next stage
	stage_ = WAIT_FOR_NEXT;

	while(gpio_get(sig_.port, sig_.number) & sig_.number);

	uint32_t temp = timer_get_counter(TIM2);
	//		(clk  / clksper second) * speed of sound (cm/s)
	//distance_ = (temp / 60e6) * 34029.0;

	//distance_ = temp * 1.0f;

	timer_set_counter(TIM2, 0);

	timer_set_oc_value(TIM2, TIM_OC1, S_1);


}

// Wait for next
void ping::wait_for_next()
{
	timer_set_counter(TIM2, 0);

	// Set next stage
	stage_ = SEND_PULSE;

}



// Constructor
ping::ping(pin sig) : 
	stage_(SEND_PULSE), distance_(0)
{
	// EXTIx exist only on pins 0, 1 and 15
	sig_ = {GPIOC, GPIO15};
}

// Initilize
void ping::init()
{
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

	// Reset timer
	timer_set_counter(TIM2, 0);

	// Step 5 enable the timer
	timer_enable_counter(TIM2);

	// Step 6 enable timer 2 interrupts
	nvic_enable_irq(NVIC_TIM2_IRQ);


	// Send first pulse
	send_pulse();
}

//Get latest reading 
float ping::get_distance()
{
	return distance_;
}

// Get time since last reading in us
float ping::get_time_since_read()
{
	return 0;
}

// Interrupt service routine for timer interrupts edge pulse
//	This will read in the value of 
//	used when the system must wait i.e. after a pulse is measured we 
//	must wait 200 us before next read
void ping::timer_isr()
{
	if(timer_get_flag(TIM2, TIM_SR_CC1IF))
	{
		timer_clear_flag(TIM2, TIM_SR_CC1IF);
		//timer_set_counter(TIM2, 0);

		switch(stage_)
		{
		case SEND_PULSE:
			send_pulse();
			break;

		case STOP_PULSE:
			stop_pulse();
			break;

		case GRAB_RESULT:
			grab_result();
			break;

		case WAIT_FOR_NEXT:
			wait_for_next();
			break;	
		}
	}
}
