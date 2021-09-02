/* 
 * File:   time_day.h
 * Author: evera
 *
 * Created on July 10, 2021, 4:55 AM
 */

#ifndef TIME_DAY_H
#define	TIME_DAY_H

#include <inttypes.h>
#include <stdbool.h>

#ifdef	__cplusplus
extern "C" {
#endif
	typedef struct
	{
		uint8_t second;
		uint8_t minute;
		uint8_t hour;
		uint8_t day_of_week;
		bool pm;
		bool f24;
	} time_day_t;

#ifdef	__cplusplus
}
#endif

#endif	/* TIME_DAY_H */

