#include "HC-SR04_Array.h"

hc_sr04_array::hc_sr04_array():
	current_interface_(IFACE_F),
	interfaces_ { 
				 interface(GPIOA, GPIO0, GPIOB, GPIO0),
				 interface(GPIOA, GPIO1, GPIOB, GPIO1),
				 interface(GPIOA, GPIO2, GPIOB, GPIO2), 
				 interface(GPIOA, GPIO3, GPIOB, GPIO3)
				},
	distance_ticks_(),
	successful_read_(false)

{

	// Setup GPIO
	// Enable gpio clock
	// TODO: find way to do this using knowledge of the pins port
	rcc_periph_clock_enable(RCC_GPIOA);
	rcc_periph_clock_enable(RCC_GPIOB);
	rcc_periph_clock_enable(RCC_GPIOC);
	rcc_periph_clock_enable(RCC_GPIOD);
	rcc_periph_clock_enable(RCC_SYSCFG);

	// Set GPIO mode
	for(uint8_t i = 0; i < NUM_INTERFACES; ++i)
	{
		pin trig = interfaces_[i].trig_;
		pin echo = interfaces_[i].echo_;
		gpio_mode_setup(trig.port_, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, trig.number_);
		gpio_mode_setup(echo.port_, GPIO_MODE_INPUT, GPIO_PUPD_NONE, echo.number_);
		gpio_clear(trig.port_, trig.number_);

		// Setup external interupts
		exti_select_source(echo.number_, echo.port_);
		exti_set_trigger(echo.number_, EXTI_TRIGGER_FALLING);
	}

	// Enable exti interupts
	// TODO put into loop above and use switch statment
	nvic_enable_irq(NVIC_EXTI0_IRQ);
	nvic_enable_irq(NVIC_EXTI1_IRQ);
	nvic_enable_irq(NVIC_EXTI2_IRQ);
	nvic_enable_irq(NVIC_EXTI3_IRQ);	

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

	// Wait for MILLIS_PER_IFACE before switching to next sonar
	if(current_ticks_ >= MILLIS_PER_IFACE)
	{
		current_ticks_ = 0;

		// Cancle any pending exti request
		exti_disable_request(interfaces_[current_interface_].echo_.number_);

		//Check if last read didn't return
		if(!successful_read_)
		{
			// No read so set to max distance
			distance_ticks_[current_interface_] = 0xFFFFFFFF;
			gpio_set(GPIOD, GPIO14);
		}
		else
		{
			gpio_clear(GPIOD, GPIO14);
		}
		successful_read_ = false;

		// Increment current sonar interface
		++current_interface_;
		if(current_interface_ >= NUM_INTERFACES)
		{
			current_interface_ = 0;
		}

		// Start next trigger
		pin trig = interfaces_[current_interface_].trig_;
		gpio_set(trig.port_, trig.number_);

		// Setupt output compare
		timer_set_counter(TIM2, 0);
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

	// Request external interrupt
	pin echo = interfaces_[current_interface_].echo_;
	exti_enable_request(echo.number_);
}

//
//		Exti interupt
//
void hc_sr04_array::extiISR()
{
	distance_ticks_[current_interface_] = timer_get_counter(TIM2);
	pin echo = interfaces_[current_interface_].echo_;

	exti_disable_request(echo.number_);
	successful_read_ = true;
}

// Static initilization
hc_sr04_array* hc_sr04_array::single_ = 0;
const uint32_t hc_sr04_array::TRIG_PULSE_WIDTH = 600;
const uint16_t hc_sr04_array::MILLIS_PER_IFACE = 25;

// None class functions (mainly isr's)

void tim2_isr(void)
{	
	// Clear the flag
	timer_clear_flag(TIM2, TIM_SR_CC1IF);
	hc_sr04_array::get_instance()->pulseTimerISR();
}

void exti0_isr(void)
{
	exti_reset_request(EXTI0);
	hc_sr04_array::get_instance()->extiISR();

}

void exti1_isr(void)
{
	exti_reset_request(EXTI1);
	hc_sr04_array::get_instance()->extiISR();
}

void exti2_isr(void)
{
	exti_reset_request(EXTI2);
	hc_sr04_array::get_instance()->extiISR();
}

void exti3_isr(void)
{
	exti_reset_request(EXTI3);
	hc_sr04_array::get_instance()->extiISR();
}
