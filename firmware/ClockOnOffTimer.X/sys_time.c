#include "sys_time.h"
#include <inttypes.h>

static volatile uint32_t sys_time_ms = 0;
static volatile uint16_t sys_time_us = 0;

void sys_time_reset()
{
	sys_time_ms = 0;
	sys_time_us = 0;
}

uint32_t sys_time_get_ms()
{
	return sys_time_ms;
}

uint16_t sys_time_get_us()
{
	return sys_time_us;
}

void sys_time_handler()
{
	sys_time_us+=100;
	if (1000 == sys_time_us)
	{
		sys_time_ms++;
		sys_time_us = 0;
	}
}
