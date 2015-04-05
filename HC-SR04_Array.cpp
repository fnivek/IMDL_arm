#include "HC-SR04_Array.h"

hc_sr04_array::hc_sr04_array():
	current_interface_(IFACE_F),
	interfaces_ { 
				 interface(GPIOB, GPIO1, GPIOB, GPIO0),
				 interface(GPIOD, GPIO1, GPIOD, GPIO0),
				 interface(GPIOC, GPIO1, GPIOC, GPIO0), 
				 interface(GPIOA, GPIO1, GPIOA, GPIO0)
				}

{

	// Setup GPIO
	// Enable gpio clock
	// TODO: find way to do this using knowledge of the pins port
	rcc_periph_clock_enable(RCC_GPIOA);
	rcc_periph_clock_enable(RCC_GPIOB);
	rcc_periph_clock_enable(RCC_GPIOC);
	rcc_periph_clock_enable(RCC_GPIOD);

	// Set GPIO mode
	for(uint8_t i = 0; i < NUM_INTERFACES; ++i)
	{
		pin trig = interfaces_[i].trig_;
		pin echo = interfaces_[i].echo_;
		gpio_mode_setup(trig.port_, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, trig.number_);
		gpio_mode_setup(echo.port_, GPIO_MODE_AF, GPIO_PUPD_NONE, echo.number_);
		gpio_clear(trig.port_, trig.number_);

	}

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

	// Step x set output compare mode
	timer_set_oc_mode(TIM2, TIM_OC1, TIM_OCM_FROZEN);

	// Step x set output compare value to 10 uS
	timer_set_oc_value(TIM2, TIM_OC1, TRIG_PULSE_WIDTH);

	// Step 5 Disable outputs
	timer_enable_oc_output(TIM2, TIM_OC1);
	timer_disable_oc_output(TIM2, TIM_OC2);
	timer_disable_oc_output(TIM2, TIM_OC3);
	timer_disable_oc_output(TIM2, TIM_OC4);

	// Reset timer
	timer_set_counter(TIM2, 0);

	// Step 5 enable the timer
	timer_enable_counter(TIM2);

	// Step 6 enable timer 2 interrupts
	timer_enable_irq(TIM2, TIM_DIER_CC1IE);
	nvic_enable_irq(NVIC_TIM2_IRQ);

	// Send first pulse
	pin trig = interfaces_[current_interface_].trig_;
	gpio_set(trig.port_, trig.number_);

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

void hc_sr04_array::systemTimerISR()
{
	++current_ticks_;
	if(current_ticks_ >= TICKS_PER_IFACE)
	{
		current_ticks_ = 0;

		++current_interface_;
		if(current_interface_ >= NUM_INTERFACES)
		{
			current_interface_ = 0;
		}

		//TODO: Check if last read didn't return

		// Start next trigger
		pin trig = interfaces_[current_interface_].trig_;
		gpio_set(trig.port_, trig.number_);

		// Setupt output compare
		timer_set_counter(TIM2, 0);
		timer_enable_oc_output(TIM2, TIM_OC1);
		// disable the timer
		timer_enable_counter(TIM2);	
	}

}

//
//		Timer isr
//
void hc_sr04_array::pulseTimerISR()
{
	// Clear the triger pin
	pin trig = interfaces_[current_interface_].trig_;
	gpio_clear(trig.port_, trig.number_);

	// Turn off output compare
	timer_disable_oc_output(TIM2, TIM_OC1);
	// disable the timer
	timer_disable_counter(TIM2);
	// Reset timer
	timer_set_counter(TIM2, 0);

	// Clear the flag
	timer_clear_flag(TIM2, TIM_SR_CC1IF);
}

// Static initilization
hc_sr04_array* hc_sr04_array::single_ = 0;
const uint32_t hc_sr04_array::TRIG_PULSE_WIDTH = 600;
const uint16_t hc_sr04_array::TICKS_PER_IFACE = 25;

// None class functions
void tim2_isr(void)
{
	hc_sr04_array::get_instance()->pulseTimerISR();
}