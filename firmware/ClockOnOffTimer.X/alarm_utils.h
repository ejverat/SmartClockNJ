/* 
 * File:   alarm_utils.h
 * Author: evera
 *
 * Created on July 18, 2021, 11:25 PM
 */

#ifndef ALARM_UTILS_H
#define	ALARM_UTILS_H

#include "alarm.h"
#include "motor_alarm.h"
#include "time_day.h"

#define MAX_ALARMS_QTY 14

#ifdef	__cplusplus
extern "C" {
#endif
	void set_motor_alarm_defaults(motor_alarm_t *motor_alarm);
	void load_motor_alarms_default();
	bool is_alarm_enabled(alarm_t *alarm);
	void disable_alarm(alarm_t *alarm);
	bool is_alarm_time(alarm_t *alarm, time_day_t *timeday);
	void motor_alarms_index_backup();
	void motor_alarms_index_restore();
	motor_alarm_t *get_first_motor_alarm();
	motor_alarm_t *get_next_motor_alarm();
	motor_alarm_t *get_prev_motor_alarm();
	uint8_t count_motor_alarms();
	motor_alarm_t *add_motor_alarm(motor_alarm_t *alarm);


#ifdef	__cplusplus
}
#endif

#endif	/* ALARM_UTILS_H */

