#include "board.h"

board::board():
	usb_(NULL),
	last_time_(0)
{

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
		board::single_->init_();
	}

	return board::single_;
}

// initialization code necessary to use the serial port
void board::init_()
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

	usb_ = usb::get_instance();

	usb_->setReadCallback(read_cb_);

	// Setup status LEDs
	rcc_periph_clock_enable(RCC_GPIOD);
	gpio_mode_setup(GPIOD, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO12 | GPIO13 | GPIO14 | GPIO15);
}

// write data to the connection to ROS
void board::write_(uint8_t* data, int length)
{
	usb_->write(data, length);
}

// returns milliseconds since start of program
unsigned long board::time_()
{
	return board::system_millis_;
}

// Updates the hardware
void board::hardwareUpdate_()
{
	usb_->poll();

	// Heartbeat every second
	if(board::system_millis_ - last_time_ > 1000)
	{
		gpio_toggle(GPIOD, GPIO12);
		last_time_ = board::system_millis_;
	}
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

// None class functions

/* Called when systick fires */
void sys_tick_handler(void)
{
	board::system_millis_++;
}

void read_cb_(void* buf, uint16_t len)
{
	gpio_toggle(GPIOD, GPIO15);
}

// Static variable inits
volatile uint32_t board::system_millis_ = 0;
board* board::single_ = NULL;