#include "motor_controler.h"

/*
 *		Motor controller constructor
 *			timer ->		The timer to use for pwm gen
 *			gpio_port ->	The gpio_port that the pins are on
 *			pin_in1 ->		Pin specifier for in1
 *			pin_in2 ->		Pin specifier for in2
 *			pin_pwm ->		pin specifier for pwm signal
 */
 // Initilize motor controller

motor_controler::motor_controler():
	pins_{	{GPIOC, GPIO10},
			{GPIOA, GPIO15},
			{GPIOA, GPIO8},
			{GPIOC, GPIO11},
			{GPIOC, GPIO12},
			{GPIOA, GPIO10}
		  }
{
	// Enable peripherials clocks
	// Timer
	rcc_periph_clock_enable(RCC_TIM1);

	// GPIO
	for(int i = 0; i < NUMBER_OF_PINS; ++i)
	{
		switch(pins_[i].port_)
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
		gpio_set_output_options(pins_[i].port_, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, pins_[i].number_);

		// PWM signals must be set up for pwm output otherwise set the pin to be an output
		if(i == LEFT_PWM || i == RIGHT_PWM)
		{
			// Set to timer one output
			gpio_mode_setup(pins_[i].port_, GPIO_MODE_AF, GPIO_PUPD_NONE, pins_[i].number_);
			gpio_set_af(pins_[i].port_, GPIO_AF1, pins_[i].number_);
		}
		else
		{
			gpio_mode_setup(pins_[i].port_, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, pins_[i].number_);
		}
	}
	


// Setup timer
	// Step 1 reset peripherial:
	timer_reset(TIM1);

	// Step 2 set mode
	timer_set_mode(TIM1, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_CENTER_1,
               TIM_CR1_DIR_UP);

	// Step 3 set output compare to PWM for both channels
	timer_set_oc_mode(TIM1, TIM_OC1, TIM_OCM_PWM1);
	timer_set_oc_mode(TIM1, TIM_OC3, TIM_OCM_PWM1);

	// Step 4 enable output compare for both channels
	timer_enable_oc_output(TIM1, TIM_OC1);
	timer_enable_oc_output(TIM1, TIM_OC3);

	// Step 5 set the compare value
	timer_set_oc_value(TIM1, TIM_OC1, 0);
	timer_set_oc_value(TIM1, TIM_OC3, 0);

	// Step 6 set the period
	timer_set_period(TIM1, pwm_ticks);

	//Step 7 enable break
	timer_enable_break_main_output(TIM1);

	// Step 8 enable the timer
	timer_enable_counter(TIM1);
}

void motor_controler::setLeftDir(direction dir)
{
	switch(dir)
	{
	case FORWARD:
		gpio_set(pins_[LEFT_IN1].port_, pins_[LEFT_IN1].number_);
		gpio_clear(pins_[LEFT_IN2].port_, pins_[LEFT_IN2].number_);
		break;

	case REVERSE:
		gpio_clear(pins_[LEFT_IN1].port_, pins_[LEFT_IN1].number_);
		gpio_set(pins_[LEFT_IN2].port_, pins_[LEFT_IN2].number_);
		break;

	case FREE_SPIN_H:
		gpio_set(pins_[LEFT_IN1].port_, pins_[LEFT_IN1].number_);
		gpio_set(pins_[LEFT_IN2].port_, pins_[LEFT_IN2].number_);
		break;

	case FREE_SPIN_L:
	default:
		gpio_clear(pins_[LEFT_IN1].port_, pins_[LEFT_IN1].number_);
		gpio_clear(pins_[LEFT_IN2].port_, pins_[LEFT_IN2].number_);
		break;

	
	}
}

void motor_controler::setRightDir(direction dir)
{
	switch(dir)
	{
	case FORWARD:
		gpio_set(pins_[RIGHT_IN2].port_, pins_[RIGHT_IN2].number_);
		gpio_clear(pins_[RIGHT_IN1].port_, pins_[RIGHT_IN1].number_);
		break;

	case REVERSE:
		gpio_clear(pins_[RIGHT_IN2].port_, pins_[RIGHT_IN2].number_);
		gpio_set(pins_[RIGHT_IN1].port_, pins_[RIGHT_IN1].number_);
		break;

	case FREE_SPIN_H:
		gpio_set(pins_[RIGHT_IN2].port_, pins_[RIGHT_IN2].number_);
		gpio_set(pins_[RIGHT_IN1].port_, pins_[RIGHT_IN1].number_);
		break;

	case FREE_SPIN_L:
	default:
		gpio_clear(pins_[RIGHT_IN2].port_, pins_[RIGHT_IN2].number_);
		gpio_clear(pins_[RIGHT_IN1].port_, pins_[RIGHT_IN1].number_);
		break;

	
	}
}
void motor_controler::setLeftDuty(float percent)
{
	if(percent >=1.0f)
	{
		timer_set_oc_value(TIM1, TIM_OC1, pwm_ticks);
	}
	else if(percent <= 0.0f)
	{
		timer_set_oc_value(TIM1, TIM_OC1, 0);
	}
	else
	{
		timer_set_oc_value(TIM1, TIM_OC1, (uint32_t)((float)pwm_ticks * percent));
	}
}

void motor_controler::setRightDuty(float percent)
{
	if(percent >=1.0f)
	{
		timer_set_oc_value(TIM1, TIM_OC3, pwm_ticks);
	}
	else if(percent <= 0.0f)
	{
		timer_set_oc_value(TIM1, TIM_OC3, 0);
	}
	else
	{
		timer_set_oc_value(TIM1, TIM_OC3, (uint32_t)((float)pwm_ticks * percent));
	}
}


motor_controler::~motor_controler()
{
	delete single_;
	single_ = NULL;
}

// Get the only instance of motor controller
motor_controler* motor_controler::get_instance()
{
	if(single_ == NULL)
	{
		single_ = new motor_controler();
	}

	return single_;
}

void motor_controler::stop()
{
	setLeftDir(FREE_SPIN_H);
	setRightDir(FREE_SPIN_H);
	setLeftDuty(0);
	setRightDuty(0);
}

// Static vars
motor_controler* motor_controler::single_ = NULL;