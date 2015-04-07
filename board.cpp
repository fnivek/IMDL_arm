#include "board.h"

board::board():
	usb_(NULL),
	heartbeat_led_(GPIOD, GPIO12), orange_led_(GPIOD, GPIO13), 
	red_led_(GPIOD, GPIO14), blue_led_(GPIOD, GPIO15),
	sonars_(NULL),
	system_millis_(0)
{
	sonars_ = hc_sr04_array::get_instance();

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

	usb_ = usb::get_instance();

	usb_->setReadCallback(read_cb_);

	// Setup status LEDs
	rcc_periph_clock_enable(RCC_GPIOD);		// TODO: case statment to activate correct gpio clock
	gpio_mode_setup(heartbeat_led_.port_, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,
		 heartbeat_led_.number_ | orange_led_.number_ | red_led_.number_ | blue_led_.number_);

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

	case IDK_4:
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
}

void read_cb_(void* buf, uint16_t len)
{
	
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
	// TODO concatenate before sending out

	// Report sonar readings
	sonar_ticks ticks = sonars_->getSonarTicks();
	// Fill buffers of data
	char front[5], back[5], front_right[5], front_left[5];
	uint32_to_str(front, ticks.front_);							// 4
	uint32_to_str(back, ticks.back_);							// 8
	uint32_to_str(front_right, ticks.front_right_);				// 12
	uint32_to_str(front_left, ticks.front_left_);				// 16

	char buf[28];

	strcpy(buf, "sonar_data\n");								// 27
	strcat(buf, front);
	strcat(buf, back);
	strcat(buf, front_right);
	strcat(buf, front_left);

	usb_->write(buf, sizeof(buf));

}

void board::update1000hz_()
{
	sonars_->systemTimerISR();
}

// Static variable inits
board* board::single_ = NULL;