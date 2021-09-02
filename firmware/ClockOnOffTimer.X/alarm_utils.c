#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include "alarm_utils.h"
#include "motor_alarm.h"
#include "time_day_utils.h"

#define IDX_DISABLED 0

typedef struct 
{
	motor_alarm_t motor_alarm;
	uint32_t index;
} indexed_motor_alarm_t;

static indexed_motor_alarm_t motor_alarms[MAX_ALARMS_QTY];
static uint8_t motor_alarms_idx = 0;
static uint8_t motor_alarms_idx_backup = 0;

void set_motor_alarm_defaults(motor_alarm_t *motor_alarm)
{
	motor_alarm->direction = RIGHT;
	motor_alarm_select_callback(motor_alarm);
	motor_alarm->alarm.time.hour = 12;
	motor_alarm->alarm.time.minute = 0;
	motor_alarm->alarm.time.second = 0;
	motor_alarm->alarm.time.pm = false;
	uint8_t day_idx;
	for (day_idx = 0; day_idx < 7; day_idx++)
	{
		motor_alarm->alarm.days[day_idx] = true;
	}
}

void load_motor_alarms_default()
{
	uint8_t idx;

	for (idx = 0; idx < MAX_ALARMS_QTY; idx++)
	{
		motor_alarms[idx].index = 0;
	}
}

bool is_alarm_enabled(alarm_t *alarm)
{
	uint8_t day;
	bool enabled = false;
	for (day = 0; day < 7; day++)
	{
		if (alarm->days[day])
		{
			enabled = true;
			break;
		}
	}

	return enabled;
}

void disable_alarm(alarm_t *alarm)
{
	uint8_t day,idx;
	for (day = 0; day < 7; day++)
	{
		alarm->days[day] = false;
	}
	for (idx = 0; idx < MAX_ALARMS_QTY; idx++)
	{
		if (motor_alarms[idx].index != IDX_DISABLED)
		{
			if (!is_alarm_enabled(&motor_alarms[idx].motor_alarm.alarm))
			{
				motor_alarms[idx].index = IDX_DISABLED;
			}
		}
	}
}

bool is_alarm_time(alarm_t *alarm, time_day_t *timeday)
{
	if (alarm->days[timeday->day_of_week-1] == true && alarm->time.pm == timeday->pm &&
			alarm->time.hour == timeday->hour && alarm->time.minute == timeday->minute &&
			alarm->time.second == timeday->second)
	{
		return true;
	}
	return false;
}

void motor_alarms_index_backup()
{
	motor_alarms_idx_backup = motor_alarms_idx;
}

void motor_alarms_index_restore()
{
	motor_alarms_idx = motor_alarms_idx_backup;
}

motor_alarm_t *get_first_motor_alarm()
{
	int16_t first_alarm_idx = -1;

	for (motor_alarms_idx = 0; motor_alarms_idx < MAX_ALARMS_QTY; motor_alarms_idx++)
	{
		if(motor_alarms[motor_alarms_idx].index != IDX_DISABLED)
		{
			if (first_alarm_idx >= 0)
			{
				if (motor_alarms[first_alarm_idx].index > motor_alarms[motor_alarms_idx].index)
				{
					first_alarm_idx = motor_alarms_idx;
				}
			}
			else
			{
				first_alarm_idx = motor_alarms_idx;
			}
		}
	}

	if (first_alarm_idx < 0)
	{
		return NULL;
	}
	motor_alarms_idx = first_alarm_idx;
	return &motor_alarms[first_alarm_idx].motor_alarm;
}
motor_alarm_t *get_next_motor_alarm()
{
	uint8_t idx;
	uint8_t next_idx = motor_alarms_idx;
	uint32_t index_val = motor_alarms[motor_alarms_idx].index;

	for(idx = 0; idx < MAX_ALARMS_QTY; idx++)
	{
		if (idx != motor_alarms_idx)
		{
			if (motor_alarms[idx].index != IDX_DISABLED)
			{
				if (motor_alarms[idx].index > index_val)
				{
					if (next_idx != motor_alarms_idx)
					{
						if (motor_alarms[idx].index < motor_alarms[next_idx].index)
							next_idx = idx;
					}
					else
					{
						next_idx = idx;
					}
				}
			}
		}
	}
	motor_alarms_idx = next_idx;
	return &motor_alarms[next_idx].motor_alarm;
}
motor_alarm_t *get_prev_motor_alarm()
{
	uint8_t idx;
	uint8_t prev_idx = motor_alarms_idx;
	uint32_t index_val = motor_alarms[motor_alarms_idx].index;

	for(idx = 0; idx < MAX_ALARMS_QTY; idx++)
	{
		if (idx != motor_alarms_idx)
		{
			if (motor_alarms[idx].index != IDX_DISABLED)
			{
				if (motor_alarms[idx].index < index_val)
				{
					if (prev_idx != motor_alarms_idx)
					{
						if (motor_alarms[idx].index > motor_alarms[prev_idx].index)
							prev_idx = idx;
					}
					else
					{
						prev_idx = idx;
					}
				}
			}
		}
	}
	motor_alarms_idx = prev_idx;
	return &motor_alarms[prev_idx].motor_alarm;
}
uint8_t count_motor_alarms()
{
	uint8_t count = 0;
	uint8_t idx;

	for (idx = 0; idx < MAX_ALARMS_QTY; idx++)
	{
		if (motor_alarms[idx].index != IDX_DISABLED)
		{
			count++;
		}
	}

	return count;
}
motor_alarm_t *add_motor_alarm(motor_alarm_t *alarm)
{
	//first get the new index value and find the first empty array position
	uint8_t idx;
	uint32_t highest_index = IDX_DISABLED;
	uint8_t count=0;
	int8_t first_disabled_idx = -1;

	for (idx = 0; idx < MAX_ALARMS_QTY; idx++)
	{
		if (motor_alarms[idx].index != IDX_DISABLED)
		{
			count++;
			if (motor_alarms[idx].index > highest_index )
			{
				highest_index =  motor_alarms[idx].index;
			}
		}
		else if(first_disabled_idx < 0)
		{
			first_disabled_idx = idx;
		}
	}

	if (count == MAX_ALARMS_QTY)
	{
		return NULL;
	}

	memcpy(&motor_alarms[first_disabled_idx].motor_alarm, alarm, sizeof(motor_alarm_t));
	motor_alarms[first_disabled_idx].index = highest_index+1;
	return &motor_alarms[first_disabled_idx].motor_alarm;
}
