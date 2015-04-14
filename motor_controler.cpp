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
		  },
	left_pos_(0),
	right_pos_(0)
{
	// Enable peripherials clocks
	// Timer
	rcc_periph_clock_enable(RCC_TIM1);
	rcc_periph_clock_enable(RCC_TIM3);
	rcc_periph_clock_enable(RCC_TIM4);

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

	// Encoder GPIO
	rcc_periph_clock_enable(RCC_GPIOB);
	gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO4 | GPIO5 | GPIO6 | GPIO7);
	gpio_set_af(GPIOB, GPIO_AF2, GPIO4 | GPIO5 | GPIO6 | GPIO7);
	


// Setup timers
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

	// Setup timer 3 and 4 to listen to the encoders
	timer_set_period(TIM3, 0xFFFF);
	timer_slave_set_mode(TIM3, 0x3); // encoder
	timer_ic_set_input(TIM3, TIM_IC1, TIM_IC_IN_TI1);
	timer_ic_set_input(TIM3, TIM_IC2, TIM_IC_IN_TI2);
	timer_enable_counter(TIM3);

	timer_set_period(TIM4, 0xFFFF);
	timer_slave_set_mode(TIM4, 0x3); // encoder
	timer_ic_set_input(TIM4, TIM_IC1, TIM_IC_IN_TI1);
	timer_ic_set_input(TIM4, TIM_IC2, TIM_IC_IN_TI2);
	timer_enable_counter(TIM4);
}

void motor_controler::setLeftDir_(direction dir)
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

void motor_controler::setRightDir_(direction dir)
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
void motor_controler::setLeftDuty_(float percent)
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

void motor_controler::setRightDuty_(float percent)
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

void motor_controler::stop_()
{
	setLeftDir_(FREE_SPIN_H);
	setRightDir_(FREE_SPIN_H);
	setLeftDuty_(0);
	setRightDuty_(0);
}

// Update the PD controlers
void motor_controler::update_()
{
	left_pos_ = timer_get_counter(TIM3);
	right_pos_ = timer_get_counter(TIM4);
}

uint16_t motor_controler::getLeftPos_()
{
	left_pos_ = timer_get_counter(TIM3);
	return left_pos_;
}

uint16_t motor_controler::getRightPos_()
{
	right_pos_ = timer_get_counter(TIM4);
	return right_pos_;
}

// Static vars
motor_controler* motor_controler::single_ = NULL;