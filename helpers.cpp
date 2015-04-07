#include "helpers.h"

void uint32_to_str(char* buf, uint32_t data)
{
	for (uint8_t i = 0; i < 4; ++i)
	{
		buf[i] = (char)(data & (uint32_t)0xFF);
		data >>= 8;
	}
	buf[4] = '\0';
}