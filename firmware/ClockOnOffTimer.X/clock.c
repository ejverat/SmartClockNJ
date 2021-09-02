#include "clock.h"
#include "config.h"
#include "time_day.h"

static time_day_t current_timeday;

time_day_t* get_rtc_timeday()
{
	bool f12_24 = false;
	bool am_pm = false;
#if defined (USE_DS3231)
	ds3231_t *clock = get_ds3231();
	ds3231_read_all(clock);

	current_timeday.day_of_week = ds3231_get_day(clock);
	current_timeday.second = ds3231_get_seconds(clock);
	current_timeday.minute = ds3231_get_minutes(clock);
	current_timeday.hour = ds3231_get_hours(clock);
#elif defined (USE_DS1307)
	ds1307_t *clock = get_ds1307();
	ds1307_read_all(clock);

	current_timeday.day_of_week = ds1307_get_day(clock);
	current_timeday.second = ds1307_get_seconds(clock);
	current_timeday.minute = ds1307_get_minutes(clock);
	current_timeday.hour = ds1307_get_hours(clock);
#endif
	if (1 == clock->data.hours.f12_24)
	{
		f12_24 = true;
	}
	if (1 == clock->data.hours.am_pm)
	{
		am_pm = true;
	}

	current_timeday.f24 = f12_24;
	current_timeday.pm = am_pm;

	return &current_timeday;
}

void set_timeday_rtc(time_day_t *timeday)
{
#if defined (USE_DS3231)
	ds3231_t *clock = get_ds3231();

	ds3231_set_day(clock, timeday->day_of_week);
	ds3231_set_seconds(clock,timeday->second);
	ds3231_set_minutes(clock, timeday->minute);
	ds3231_set_hours_f12(clock, timeday->hour, timeday->pm);
#elif defined (USE_DS1307)
	ds1307_t *clock = get_ds1307();

	ds1307_set_day(clock, timeday->day_of_week);
	ds1307_set_seconds(clock,timeday->second);
	ds1307_set_minutes(clock, timeday->minute);
	ds1307_set_hours_f12(clock, timeday->hour, timeday->pm);
#endif
}
