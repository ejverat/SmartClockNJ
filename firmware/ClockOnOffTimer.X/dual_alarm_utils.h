/* 
 * File:   dual_alarm_utils.h
 * Author: evera
 *
 * Created on August 13, 2021, 1:10 AM
 */

#ifndef DUAL_ALARM_UTILS_H
#define	DUAL_ALARM_UTILS_H

#include "dual_day_alarm.h"
#include "time_day.h"

#ifdef	__cplusplus
extern "C" {
#endif

	void set_dual_alarm_to_defaults(dual_day_alarm_t* alarm);
	void check_dual_alarm(dual_day_alarm_t *alarm, time_day_t *timeday);


#ifdef	__cplusplus
}
#endif

#endif	/* DUAL_ALARM_UTILS_H */

