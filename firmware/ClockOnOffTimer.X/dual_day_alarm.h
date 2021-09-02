/* 
 * File:   dual_day_alarm.h
 * Author: evera
 *
 * Created on August 12, 2021, 8:10 AM
 */

#ifndef DUAL_DAY_ALARM_H
#define	DUAL_DAY_ALARM_H

#include <stdint.h>
#include "day_alarm.h"

#ifdef	__cplusplus
extern "C" {
#endif

	typedef struct 
	{
		day_alarm_t alarm1;
		day_alarm_t alarm2;
		uint8_t day;
	} dual_day_alarm_t;




#ifdef	__cplusplus
}
#endif

#endif	/* DUAL_DAY_ALARM_H */

