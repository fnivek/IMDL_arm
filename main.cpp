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
#include <libopencm3/stm32/exti.h>
#include <libopencm3/stm32/timer.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/stm32/syscfg.h>

uint32_t system_millis = 0;

// make c++ happy
 void *__dso_handle;
 
int __cxa_atexit(void (*destructor) (void *), void *arg, void *dso);
void __cxa_finalize(void *f);


void tim2_isr(void)
{	
	// Clear the flag
	timer_clear_flag(TIM2, TIM_SR_CC1IF);
}

void exti0_isr(void)
{
	// Clear the flag
	exti_reset_request(EXTI0);

	gpio_toggle(GPIOD, GPIO12);
	//exti_enable_request(EXTI0);

}

/* Called when systick fires */
void sys_tick_handler(void)
{
	system_millis++;
}

/* Set up a timer to create 1mS ticks. */
void systick_setup_(void)
{
	/* clock rate / 1000 to get 1mS interrupt rate */
	systick_set_reload(120000);
	systick_set_clocksource(STK_CSR_CLKSOURCE_AHB);
	systick_counter_enable();
	/* this done last */
	systick_interrupt_enable();
}


int main(void)
{
	// Init
	rcc_clock_setup_hse_3v3(&hse_8mhz_3v3[CLOCK_3V3_120MHZ]);


	systick_setup_();

	// Setup status LEDs
	rcc_periph_clock_enable(RCC_GPIOD);		// TODO: case statment to activate correct gpio clock
	gpio_mode_setup(GPIOD, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO12 | GPIO13 | GPIO14 | GPIO15);

	// Setup GPIO
	// Enable gpio clock
	rcc_periph_clock_enable(RCC_GPIOA);
	rcc_periph_clock_enable(RCC_GPIOB);

	// Set GPIO mode
	gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO0);
	gpio_mode_setup(GPIOB, GPIO_MODE_INPUT, GPIO_PUPD_NONE, GPIO0);				// This line was set to alternate function!!!!!!
	gpio_clear(GPIOA, GPIO0);

	// Setup external interupts
	//exti_select_source(EXTI0, GPIOB);
	//exti_set_trigger(EXTI0, EXTI_TRIGGER_BOTH);
	//exti_enable_request(EXTI0);
	EXTI_IMR |= 1;
	EXTI_FTSR |= 1;
	SYSCFG_EXTICR(0) = (SYSCFG_EXTICR(0) & ~0xF0)| 0x10;


	// Enable exti interupts
	nvic_enable_irq(NVIC_EXTI0_IRQ);	

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
	timer_set_oc_value(TIM2, TIM_OC1, 600);
	// Step 5 Disable outputs
	timer_enable_oc_output(TIM2, TIM_OC1);
	// Reset timer
	timer_set_counter(TIM2, 0);
	// Step 5 enable the timer
	timer_enable_counter(TIM2);
	// Step 6 enable timer 2 interrupts
	timer_enable_irq(TIM2, TIM_DIER_CC1IE);
	nvic_enable_irq(NVIC_TIM2_IRQ);

	// Send first pulse
	gpio_set(GPIOA, GPIO0);

	while (1) {

	}
}
