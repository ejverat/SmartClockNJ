/* 
 * File:   alarm.h
 * Author: evera
 *
 * Created on July 16, 2021, 12:30 AM
 */

#ifndef ALARM_H
#define	ALARM_H

#include <stdbool.h>

#include "time_day.h"

#ifdef	__cplusplus
extern "C" {
#endif
	typedef struct 
	{
		uint8_t hour;
		uint8_t minute;
		uint8_t second;
		bool pm;
	} f12_hour_t;

	typedef struct 
	{
		f12_hour_t time;
		bool days[7];
		void (*callback_fn) (void);
	} alarm_t;


#ifdef	__cplusplus
}
#endif

#endif	/* ALARM_H */

