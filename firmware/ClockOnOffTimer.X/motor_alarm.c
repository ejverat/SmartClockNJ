#include <inttypes.h>

#include "motor_alarm.h"
#include "motor.h"
#include "config.h"
#include "sys_time.h"
#include "motor_utils.h"

static void motor_spin_to_right();
static void motor_spin_to_left();

void motor_alarm_select_callback(motor_alarm_t *alarm)
{
	if( RIGHT == alarm->direction)
	{
		alarm->alarm.callback_fn = motor_spin_to_right;
	}
	else
	{
		alarm->alarm.callback_fn = motor_spin_to_left;
	}
}

static void motor_spin_to_right()
{
	motor_t *motor = get_motor();
	motor->direction = RIGHT;
	spin_motor(motor);
}

static void motor_spin_to_left()
{
	motor_t *motor = get_motor();
	motor->direction = LEFT;
	spin_motor(motor);
}
