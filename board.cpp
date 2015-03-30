#include "board.h"

board::board():
	usb_()
{

}

// initialization code necessary to use the serial port
void board::init()
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

	systick_setup();


	usb_.init();
}

// read a byte from the serial port. -1 = failure
int board::read()
{
	return usb_.read();
}

// write data to the connection to ROS
void board::write(uint8_t* data, int length)
{
	usb_.write(data, length);
}

// returns milliseconds since start of program
unsigned long board::time()
{
	return board::system_millis;
}

// Updates the hardware
void board::hardwareUpdate()
{
	usb_.poll();
}

/* monotonically increasing number of milliseconds from reset
 * overflows every 49 days if you're wondering
 */
volatile uint32_t system_millis = 0;

/* Called when systick fires */
void board::sys_tick_handler(void)
{
	board::system_millis++;
}

/* Set up a timer to create 1mS ticks. */
void board::systick_setup(void)
{
	/* clock rate / 1000 to get 1mS interrupt rate */
	systick_set_reload(120000);
	systick_set_clocksource(STK_CSR_CLKSOURCE_AHB);
	systick_counter_enable();
	/* this done last */
	systick_interrupt_enable();
}

volatile uint32_t board::system_millis = 0;