/* 
 * File:   clock.h
 * Author: evera
 *
 * Created on July 16, 2021, 1:19 AM
 */

#ifndef CLOCK_H
#define	CLOCK_H

#include "time_day.h"

#ifdef	__cplusplus
extern "C" {
#endif

	time_day_t* get_rtc_timeday();
	void set_timeday_rtc(time_day_t *timeday);



#ifdef	__cplusplus
}
#endif

#endif	/* CLOCK_H */

