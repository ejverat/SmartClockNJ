/* 
 * File:   motor_alarm.h
 * Author: evera
 *
 * Created on July 16, 2021, 3:53 AM
 */

#ifndef MOTOR_ALARM_H
#define	MOTOR_ALARM_H

#include <inttypes.h>

#include "motor.h"
#include "alarm.h"

#define RIGHT direction1
#define LEFT  direction2

#ifdef	__cplusplus
extern "C" {
#endif

	typedef struct 
	{
		alarm_t alarm;
		motor_direction_t direction;
	} motor_alarm_t;

	void motor_alarm_select_callback(motor_alarm_t *alarm);



#ifdef	__cplusplus
}
#endif

#endif	/* MOTOR_ALARM_H */

