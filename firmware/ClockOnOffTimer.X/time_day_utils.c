#include "time_day_utils.h"

#define MIN_SECOND_VALUE 0
#define MAX_SECOND_VALUE 59
#define MIN_MINUTE_VALUE 0
#define MAX_MINUTE_VALUE 59
#define MIN_HOUR_VALUE_F24 0
#define MAX_HOUR_VALUE_F24 23
#define MIN_HOUR_VALUE_FAMPM 1
#define MAX_HOUR_VALUE_FAMPM 12
#define MIN_DAY_OF_WEEK_VALUE 1
#define MAX_DAY_OF_WEEK_VALUE 7

bool is_valid_day_of_week(uint8_t day_of_week)
{
	return (day_of_week >= MIN_DAY_OF_WEEK_VALUE && day_of_week <= MAX_DAY_OF_WEEK_VALUE);
}
bool is_valid_hour_f12(uint8_t hours)
{
	return (hours >= MIN_HOUR_VALUE_FAMPM && hours <= MAX_HOUR_VALUE_FAMPM);
}
bool is_valid_minutes(uint8_t minutes)
{
	return (minutes >= MIN_MINUTE_VALUE && minutes <= MAX_MINUTE_VALUE);
}
bool is_valid_second(uint8_t seconds)
{
	return (seconds >= MIN_SECOND_VALUE && seconds <= MAX_SECOND_VALUE);
}
uint8_t roll_inc_day_of_week(uint8_t day_of_week)
{
	if (day_of_week >= MAX_DAY_OF_WEEK_VALUE)
		return MIN_DAY_OF_WEEK_VALUE;
	return day_of_week+1;
}
uint8_t roll_inc_hour_f12(uint8_t hours)
{
	if (hours >= MAX_HOUR_VALUE_FAMPM)
		return MIN_HOUR_VALUE_FAMPM;
	return hours+1;
}
uint8_t roll_inc_minute(uint8_t minutes)
{
	if (minutes >= MAX_MINUTE_VALUE)
		return MIN_MINUTE_VALUE;
	return minutes+1;
}
uint8_t roll_inc_second(uint8_t seconds)
{
	if (seconds >= MAX_SECOND_VALUE)
		return MIN_SECOND_VALUE;
	return seconds+1;
}

uint8_t roll_dec_day_of_week(uint8_t day_of_week)
{
	if (day_of_week == MIN_DAY_OF_WEEK_VALUE)
		return MAX_DAY_OF_WEEK_VALUE;
	return day_of_week-1;
}
uint8_t roll_dec_hour_f12(uint8_t hours)
{
	if (hours == MIN_HOUR_VALUE_FAMPM)
		return MAX_HOUR_VALUE_FAMPM;
	return hours-1;
}
uint8_t roll_dec_minute(uint8_t minutes)
{
	if (minutes == MIN_MINUTE_VALUE)
		return MAX_MINUTE_VALUE;
	return minutes-1;
}
uint8_t roll_dec_second(uint8_t seconds)
{
	if (seconds == MIN_SECOND_VALUE)
		return MAX_SECOND_VALUE;
	return seconds-1;
}
