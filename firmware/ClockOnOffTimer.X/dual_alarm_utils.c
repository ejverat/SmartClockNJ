#include <stddef.h>
#include "dual_alarm_utils.h"

void set_dual_alarm_to_defaults(dual_day_alarm_t* alarm)
{
	alarm->day = 1;
	alarm->alarm1.time.pm = false;
	alarm->alarm1.time.second = 0;
	alarm->alarm1.time.minute = 0;
	alarm->alarm1.time.hour = 5;
	alarm->alarm2.time.pm = true;
	alarm->alarm2.time.second = 0;
	alarm->alarm2.time.minute = 0;
	alarm->alarm2.time.hour = 5;
}

void check_dual_alarm(dual_day_alarm_t *alarm, time_day_t *timeday)
{
	if (alarm->alarm1.callback_fn != NULL &&
			alarm->alarm1.time.pm == timeday->pm &&
			alarm->alarm1.time.second == timeday->second &&
			alarm->alarm1.time.minute == timeday->minute &&
			alarm->alarm1.time.hour == timeday->hour)
	{
		alarm->alarm1.callback_fn();
	}
	if (alarm->alarm2.callback_fn != NULL &&
			alarm->alarm2.time.pm == timeday->pm &&
			alarm->alarm2.time.second == timeday->second &&
			alarm->alarm2.time.minute == timeday->minute &&
			alarm->alarm2.time.hour == timeday->hour)
	{
		alarm->alarm2.callback_fn();
	}
}
