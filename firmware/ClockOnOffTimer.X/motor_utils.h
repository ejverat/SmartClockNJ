/* 
 * File:   motor_utils.h
 * Author: evera
 *
 * Created on August 13, 2021, 1:32 AM
 */

#ifndef MOTOR_UTILS_H
#define	MOTOR_UTILS_H

#include <stdint.h>
#include "motor.h"

#ifdef	__cplusplus
extern "C" {
#endif

	void spin_motor(motor_t *motor);
	void spin_motor_left(motor_t *motor);
	void spin_motor_right(motor_t *motor);
	void motor_off(motor_t *motor);
	void motor_spin_time_monitor(motor_t *motor, uint32_t time);


#ifdef	__cplusplus
}
#endif

#endif	/* MOTOR_UTILS_H */

