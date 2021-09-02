/* 
 * File:   time_day_utils.h
 * Author: evera
 *
 * Created on July 16, 2021, 1:57 AM
 */

#ifndef TIME_DAY_UTILS_H
#define	TIME_DAY_UTILS_H

#include <stdbool.h>
#include <inttypes.h>

#ifdef	__cplusplus
extern "C" {
#endif

	bool is_valid_day_of_week(uint8_t day_of_week);
	bool is_valid_hour_f12(uint8_t hours);
	bool is_valid_minutes(uint8_t minutes);
	bool is_valid_second(uint8_t seconds);
	uint8_t roll_inc_day_of_week(uint8_t day_of_week);
	uint8_t roll_inc_hour_f12(uint8_t hours);
	uint8_t roll_inc_minute(uint8_t minutes);
	uint8_t roll_inc_second(uint8_t seconds);
	uint8_t roll_dec_day_of_week(uint8_t day_of_week);
	uint8_t roll_dec_hour_f12(uint8_t hours);
	uint8_t roll_dec_minute(uint8_t minutes);
	uint8_t roll_dec_second(uint8_t seconds);

#ifdef	__cplusplus
}
#endif

#endif	/* TIME_DAY_UTILS_H */

