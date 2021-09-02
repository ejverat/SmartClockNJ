#include <xc.h>
#include <stdbool.h>
#include <inttypes.h>

#include "button.h"
#include "mcc_generated_files/pin_manager.h"
#include "sys_time.h"


#define DEBOUNCE_TIME_MS 100

static bool button_ok_status();
static bool button_inc_status();
static bool button_dec_status();

static void wait_debounce();

button_t get_user_input()
{
	if (button_ok_status() || button_dec_status() || button_inc_status())
	{
		wait_debounce();
		if (button_ok_status())
		{
			return button_ok;
		}
		else if (button_inc_status())
		{
			return button_inc;
		}
		else if (button_dec_status())
		{
			return button_dec;
		}
	}

	return button_none;
}

static bool button_ok_status()
{
	return BUTTON1_GetValue() == LOW;
}
static bool button_inc_status()
{
	return BUTTON0_GetValue() == LOW;
}
static bool button_dec_status()
{
	return BUTTON2_GetValue() == LOW;
}
static void wait_debounce()
{
	uint32_t start_time = sys_time_get_ms();

	while (sys_time_get_ms() - start_time < DEBOUNCE_TIME_MS);
}
