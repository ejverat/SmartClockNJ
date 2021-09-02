/* 
 * File:   user_input.h
 * Author: evera
 *
 * Created on July 16, 2021, 2:09 AM
 */

#ifndef USER_INPUT_H
#define	USER_INPUT_H

#include <inttypes.h>
#include <stdbool.h>

#include "time_day.h"

#ifdef	__cplusplus
extern "C" {
#endif
	typedef struct 
	{
		uint8_t max_val;
		uint8_t min_val;
		uint8_t user_val;
	} input_numeric_t;

	typedef struct 
	{
		char *option1_str;
		char *option2_str;
		bool user_option1;
	} input_binary_t;

	typedef struct 
	{
		char *display_format;
		time_day_t *timeday;
	} input_timeday_t;

	typedef struct 
	{
		char *text;
		const uint8_t col;
		const uint8_t row;
	} 
	user_input_t;


#ifdef	__cplusplus
}
#endif

#endif	/* USER_INPUT_H */

