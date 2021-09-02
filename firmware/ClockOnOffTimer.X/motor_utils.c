#include "motor_utils.h"
#include "motor.h"
#include "sys_time.h"

static uint32_t on_start_time;

void spin_motor(motor_t *motor)
{
	if (motor->direction == direction1)
	{
		motor->pin_dir1_high_fn();
		motor->pin_dir2_low_fn();
	}
	else if (motor->direction == direction2)
	{
		motor->pin_dir1_low_fn();
		motor->pin_dir2_high_fn();
	}
	on_start_time = sys_time_get_ms();
}
void spin_motor_left(motor_t *motor)
{
	motor->direction = direction2;
	motor->pin_dir1_low_fn();
	motor->pin_dir2_high_fn();
	on_start_time = sys_time_get_ms();

}
void spin_motor_right(motor_t *motor)
{
	motor->direction = direction1;
	motor->pin_dir1_high_fn();
	motor->pin_dir2_low_fn();
	on_start_time = sys_time_get_ms();
}

void motor_off(motor_t *motor)
{
	motor->direction = off;
	motor->pin_dir1_low_fn();
	motor->pin_dir2_low_fn();
}

void motor_spin_time_monitor(motor_t *motor, uint32_t time)
{
	if (motor->direction != off)
	{
		if (sys_time_get_ms() - on_start_time > time)
		{
			motor_off(motor);
		}
	}
}
