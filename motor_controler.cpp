#include "motor_controler.h"

/*
 *		Motor controller constructor
 *			timer ->		The timer to use for pwm gen
 *			gpio_port ->	The gpio_port that the pins are on
 *			pin_in1 ->		Pin specifier for in1
 *			pin_in2 ->		Pin specifier for in2
 *			pin_pwm ->		pin specifier for pwm signal
 */
motor_controler::motor_controler(pin m1_in1, pin m1_in2, pin m1_pwm,
		pin m2_in1, pin m2_in2, pin m2_pwm)
{
	// Initilize member vars
	// TODO eroror checking
	//		TIM1_CH1 exist only on ~PA7, PA8, ~PB13, ~PE8, PE9
	//		TIM1_CH2 exist only on PA9, ~PB0, ~PB14, ~PE10, PE11
	pins_[M1_IN1] = m1_in1;
	pins_[M1_IN2] = m1_in2;
	pins_[M1_PWM] = m1_pwm;

	pins_[M2_IN1] = m2_in1;
	pins_[M2_IN2] = m2_in2;
	pins_[M2_PWM] = m2_pwm;
}

void motor_controler::init(void)
{
	// Enable peripherials
	// Timer
	rcc_periph_clock_enable(RCC_TIM1);

	// GPIO
	for(int i = 0; i < NUMBER_OF_PINS; ++i)
	{
		switch(pins_[i].port)
		{
		case GPIOA:
			rcc_periph_clock_enable(RCC_GPIOA);
			break;

		case GPIOB:
			rcc_periph_clock_enable(RCC_GPIOB);
			break;
			
		case GPIOC:
			rcc_periph_clock_enable(RCC_GPIOC);
			break;
			
		case GPIOD:
			rcc_periph_clock_enable(RCC_GPIOD);
			break;
			
		case GPIOE:
			rcc_periph_clock_enable(RCC_GPIOE);
			break;
			
		case GPIOF:
			rcc_periph_clock_enable(RCC_GPIOF);
			break;

		default:
			// TODO: throw error
			break;
		}

		// Step 1 set output options (push pull) output, no pull up or pull down
		gpio_set_output_options(pins_[i].port, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, pins_[i].number);

		// PWM signals must be set up for pwm output otherwise set the pin to be an output
		if(i == M1_PWM || i == M2_PWM)
		{
			// Set to timer one output
			gpio_mode_setup(pins_[i].port, GPIO_MODE_AF, GPIO_PUPD_NONE, pins_[i].number);
			gpio_set_af(pins_[i].port, GPIO_AF1, pins_[i].number);
		}
		else
		{
			gpio_mode_setup(pins_[i].port, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, pins_[i].number);
		}
	}
	


// Setup timer
	// Step 1 reset peripherial:
	timer_reset(TIM1);

	// Step 2 set mode to // is there a mode per chn???
	timer_set_mode(TIM1, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_CENTER_1,
               TIM_CR1_DIR_UP);

	// Step 3 set output compare to PWM for both channels
	timer_set_oc_mode(TIM1, TIM_OC1, TIM_OCM_PWM1);
	timer_set_oc_mode(TIM1, TIM_OC3, TIM_OCM_PWM1);

	// Step 4 enable output compare for both channels
	timer_enable_oc_output(TIM1, TIM_OC1);
	timer_enable_oc_output(TIM1, TIM_OC3);

	// Step 5 set the compare value
	timer_set_oc_value(TIM1, TIM_OC1, 200);
	timer_set_oc_value(TIM1, TIM_OC3, 200);

	// Step 6 set the period
	timer_set_period(TIM1, 1000);

	//Step 7 enable break
	timer_enable_break_main_output(TIM1);

	// Step 8 enable the timer
	timer_enable_counter(TIM1);
}

void motor_controler::set_m1_dir(direction dir)
{
	switch(dir)
	{
	case FORWARD:
		gpio_set(pins_[M1_IN1].port, pins_[M1_IN1].number);
		gpio_clear(pins_[M1_IN2].port, pins_[M1_IN2].number);
		break;

	case REVERSE:
		gpio_clear(pins_[M1_IN1].port, pins_[M1_IN1].number);
		gpio_set(pins_[M1_IN2].port, pins_[M1_IN2].number);
		break;

	case FREE_SPIN_H:
		gpio_set(pins_[M1_IN1].port, pins_[M1_IN1].number);
		gpio_set(pins_[M1_IN2].port, pins_[M1_IN2].number);
		break;

	case FREE_SPIN_L:
	default:
		gpio_clear(pins_[M1_IN1].port, pins_[M1_IN1].number);
		gpio_clear(pins_[M1_IN2].port, pins_[M1_IN2].number);
		break;

	
	}
}