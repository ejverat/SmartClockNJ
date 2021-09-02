/* 
 * File:   day_alarm.h
 * Author: evera
 *
 * Created on August 13, 2021, 2:53 AM
 */

#ifndef DAY_ALARM_H
#define	DAY_ALARM_H

#include "alarm.h"

#ifdef	__cplusplus
extern "C" {
#endif

	typedef struct 
	{
		f12_hour_t time;
		void (*callback_fn)(void);
	} day_alarm_t;



#ifdef	__cplusplus
}
#endif

#endif	/* DAY_ALARM_H */

