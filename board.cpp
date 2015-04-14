#include "board.h"

board::board():
	usb_(NULL),
	heartbeat_led_(GPIOD, GPIO12), orange_led_(GPIOD, GPIO13), 
	red_led_(GPIOD, GPIO14), blue_led_(GPIOD, GPIO15),
	sonars_(NULL),
	system_millis_(0),
	recieved_comm_heartbeat_(false)
{
	/* Initilize the clock to: 
		.pllm = 25,
		.plln = 240,
		.pllp = 2,
		.pllq = 5,
		.hpre = RCC_CFGR_HPRE_DIV_NONE,
		.ppre1 = RCC_CFGR_PPRE_DIV_4,
		.ppre2 = RCC_CFGR_PPRE_DIV_2,
		.power_save = 1,
		.flash_config = FLASH_ACR_ICE | FLASH_ACR_DCE |
			FLASH_ACR_LATENCY_3WS,
		.apb1_frequency = 30000000,
		.apb2_frequency = 60000000,
  	*/
	rcc_clock_setup_hse_3v3(&hse_8mhz_3v3[CLOCK_3V3_120MHZ]);

	systick_setup_();

	// Setup sonars
	sonars_ = hc_sr04_array::get_instance();

	// Setup usb
	usb_ = usb::get_instance();
	usb_->setReadCallback(read_cb_);

	// Setup motors
	motors_ = motor_controler::get_instance();
	motors_->stop_();

	// Setup status LEDs
	rcc_periph_clock_enable(RCC_GPIOD);		// TODO: case statment to activate correct gpio clock
	gpio_mode_setup(heartbeat_led_.port_, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,
		 heartbeat_led_.number_ | orange_led_.number_ | red_led_.number_ | blue_led_.number_);

	// Set initial status
	setStatus_(OK);
}

board::~board()
{
	delete board::single_;
	board::single_ = NULL;
}

board* board::get_instance()
{
	if(board::single_ == NULL)
	{
		board::single_ = new board();
	}

	return board::single_;
}

// write data to the connection to ROS
void board::write_(uint8_t* data, int length)
{
	usb_->write(data, length);
}

// Updates the hardware
void board::hardwareUpdate_()
{
	usb_->poll();
}

/* monotonically increasing number of milliseconds from reset
 * overflows every 49 days if you're wondering
 */
volatile uint32_t system_millis_ = 0;



/* Set up a timer to create 1mS ticks. */
void board::systick_setup_(void)
{
	/* clock rate / 1000 to get 1mS interrupt rate */
	systick_set_reload(120000);
	systick_set_clocksource(STK_CSR_CLKSOURCE_AHB);
	systick_counter_enable();
	/* this done last */
	systick_interrupt_enable();
}

void board::setStatus_(status_ status)
{
	switch(status)
	{
	case OK:
		gpio_clear(heartbeat_led_.port_, red_led_.number_ | orange_led_.number_ | blue_led_.number_);
		break;

	case IDK_1:
		gpio_set(heartbeat_led_.port_, orange_led_.number_);
		gpio_clear(heartbeat_led_.port_, red_led_.number_ | blue_led_.number_);
		break;

	case ERROR:
		gpio_set(heartbeat_led_.port_, red_led_.number_);
		gpio_clear(heartbeat_led_.port_, orange_led_.number_ | blue_led_.number_);
		break;

	case IDK_3:
		gpio_set(heartbeat_led_.port_, red_led_.number_ | orange_led_.number_);
		gpio_clear(heartbeat_led_.port_, blue_led_.number_);
		break;

	case MISSED_HEARTBEAT:
		gpio_set(heartbeat_led_.port_, blue_led_.number_);
		gpio_clear(heartbeat_led_.port_, red_led_.number_ | orange_led_.number_);
		break;

	case IDK_5:
		gpio_set(heartbeat_led_.port_, blue_led_.number_ | orange_led_.number_);
		gpio_clear(heartbeat_led_.port_, red_led_.number_);
		break;

	case IDK_6:
		gpio_set(heartbeat_led_.port_, blue_led_.number_ | red_led_.number_);
		gpio_clear(heartbeat_led_.port_, orange_led_.number_);
		break;

	case IDK_2:
		gpio_set(heartbeat_led_.port_, blue_led_.number_ | orange_led_.number_ | red_led_.number_);
		break;
	}
}

void board::beat_()
{
	gpio_toggle(heartbeat_led_.port_, heartbeat_led_.number_);
}

// None class functions

/* Called when systick fires */
void sys_tick_handler(void)
{
	board* bd = board::get_instance();
	bd->system_millis_++;

	// 1000 Hz updates
	bd->update1000hz_();

	// 100 Hz updates

	// 10 Hz updates
	if(!(bd->system_millis_ % 100))
	{
		bd->update10hz_();
	}

	// 1 Hz updates
	if(!(bd->system_millis_ % 1000))
	{
		bd->update1hz_();
	}

	// 0.5 Hz updates
	if(!(bd->system_millis_ % 2000))
	{
		bd->updateHalfHz_();
	}
}

void read_cb_(char* buf, uint16_t len)
{
	if(len == 64)
	{
		// TODO: deal with strings of length 64
		return;
	}

	// Add a null terminator to the end to work with string.h
	buf[len] = '\0';

	// Search for left and right
	char* left = strstr(buf, board::left_duty_id_);
	char* right = strstr(buf, board::right_duty_id_);
	char* heartbeat = strstr(buf, board::heartbeat_id_);

	board* bd = board::get_instance();

	// Reset heart beat timer if we have any message
	if(right != NULL || left != NULL || heartbeat != NULL)
	{
		bd->recieved_comm_heartbeat_ = true;
	}

	// Found a match to the left
	if(left != NULL)
	{
		// Read in the value 
		// Not sure why I need a intermidiate but I do...
		uint32_t duty_temp = (*(reinterpret_cast<uint32_t*>(&left[9])));
		float duty = *(reinterpret_cast<float*>(&duty_temp));

		// Set wheel dir
		if(duty > 0)
		{
			bd->motors_->setLeftDir_(motor_controler::FORWARD);
			bd->motors_->setLeftDuty_(duty);
		}
		else if (duty < 0)
		{
			bd->motors_->setLeftDir_(motor_controler::REVERSE);
			bd->motors_->setLeftDuty_(duty * -1);
		}
		else
		{
			bd->motors_->setLeftDuty_(0);
		}

	}

	// Found a match to right
	if(right != NULL)
	{
		// Read in the value 
		uint32_t duty_temp = (*(reinterpret_cast<uint32_t*>(&right[10])));
		float duty = *(reinterpret_cast<float*>(&duty_temp));

		// Set wheel dir
		if(duty > 0)
		{
			bd->motors_->setRightDir_(motor_controler::FORWARD);
			bd->motors_->setRightDuty_(duty);
		}
		else if (duty < 0)
		{
			bd->motors_->setRightDir_(motor_controler::REVERSE);
			bd->motors_->setRightDuty_(duty * -1);
		}
		else
		{
			bd->motors_->setRightDuty_(0);
		}
	}
}

void board::updateHalfHz_()
{
	if(!recieved_comm_heartbeat_)
	{
		// Stop the wheels now!
		motors_->setRightDuty_(0);
		motors_->setLeftDuty_(0);

		setStatus_(board::MISSED_HEARTBEAT);
	}
	else
	{
		setStatus_(board::OK);
	}

	recieved_comm_heartbeat_ = false;

}

// 1 Hz update function
//		Contains heart beat
void board::update1hz_()
{
	beat_();
}

// 10 Hz update function
//		Contains sonar out
void board::update10hz_()
{
	// Report sonar readings
	sonar_ticks ticks = sonars_->getSonarTicks();

	// Fill buffers of data
	char* range_data = reinterpret_cast<char*>(&ticks);

	// Ugh this is nasty...
	char buf[] = { 's', 'o', 'n', 'a', 'r', '_', 'd', 'a', 't', 'a', 
		range_data[0], 			range_data[1], 		range_data[2], 		range_data[3],
		range_data[4], 			range_data[5], 		range_data[6], 		range_data[7],
		range_data[8], 			range_data[9], 		range_data[10], 	range_data[11],
		range_data[12], 		range_data[13], 	range_data[14], 	range_data[15]
				 };
	
	uint16_t bytes_writen = usb_->write(buf, sizeof(buf));

	// Report motor pos
	motors_->update_();

	if( bytes_writen != 0)
	{
		uint16_t left = motors_->getLeftPos_();
		uint16_t right = motors_->getRightPos_();
		char* left_char = reinterpret_cast<char*>(&left);
		char* right_char = reinterpret_cast<char*>(&right);
		char bufl[] = { 'm', 'o', 't', 'o', 'r', '_', 'p', 'o', 's',
							left_char[0], left_char[1],
							right_char[0], right_char[1]
						};
		uint8_t trys = 100;
		do 
		{
			bytes_writen = usb_->write(bufl, sizeof(bufl));
			--trys;
		} while(bytes_writen == 0 && trys != 0);
	}

}

void board::update1000hz_()
{
	sonars_->systemTimerISR();
}

// Static variable inits
board* board::single_ = NULL;
const char board::left_duty_id_[] = "left_duty";
const char board::right_duty_id_[] = "right_duty";
const char board::heartbeat_id_[] = "beat";
