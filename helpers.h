#ifndef HELPERS_H
#define HELPERS_H

// TODO find where standard uint come from
#include <libopencm3/stm32/gpio.h>

/*
 * Structure for a specific pin
 */
typedef struct pin
{
	uint32_t port_;
	uint16_t number_;

	pin(uint32_t port, uint16_t number):
		port_(port), number_(number)
	{}

	pin():
		port_(0), number_(0)
	{}

} pin;

/*
 * Convert a uint32 to big endian c string
 *		buf must be exactly 5 chars long (5th char is '\0')
 */
void uint32_to_str(char* buf, uint32_t data);

#endif