/* 
 * File:   display_utils.h
 * Author: evera
 *
 * Created on July 16, 2021, 2:27 AM
 */

#ifndef DISPLAY_UTILS_H
#define	DISPLAY_UTILS_H

#include <stdbool.h>
#include <stdio.h>

#include "user_input.h"
#include "time_day.h"
#include "alarm.h"
#include "motor_alarm.h"
#include "dual_day_alarm.h"
#include "day_alarm.h"
#include "mode.h"

const char day_str[7][4] = {
	"SUN","MON","TUE","WED","THR","FRI","SAT"
};

const char hour_pm_am_str[2][3] = {"AM","PM"};
const char day_enabled_str[2] = {'X','E'};
const char motor_direction_str[2][6] = {"RIGHT","LEFT"};
const char alarm_type_str[2][6] = {"ON ","OFF"};
const char mode_str[3][7] = {"PIR","ALARM","MANUAL"};
const char alarm_status_str[2][9] = {"INACTIVE","ACTIVE  "};
//  0123456789012345
// "DAY hh:mm:ss PM "
// "    hh:mm:ss PM "
const char screen_dual_alarm[2][17] = { "      :  :      ",
				  	"      :  :      "};
user_input_t ui_alarm_day = {.col=0,.row=0};
user_input_t ui_alarm_hour1 = {.col=4,.row=0};
user_input_t ui_alarm_minute1 = {.col=7,.row=0};
user_input_t ui_alarm_second1 = {.col=10,.row=0};
user_input_t ui_alarm_pm_am1 = {.col=13,.row=0};
user_input_t ui_alarm_hour2 = {.col=4,.row=1};
user_input_t ui_alarm_minute2 = {.col=7,.row=1};
user_input_t ui_alarm_second2 = {.col=10,.row=1};
user_input_t ui_alarm_pm_am2 = {.col=13,.row=1};

//  0123456789012345
// "DAY hh:mm:ss PM "
// "OFF     INACTIVE"

const char screen_edit_alarm[2][17] = { "      :  :      ",
					"                "};
user_input_t ui_edit_alarm_day = {.col=0,.row=0};
user_input_t ui_edit_alarm_hour = {.col=4,.row=0};
user_input_t ui_edit_alarm_minute = {.col=7,.row=0};
user_input_t ui_edit_alarm_second = {.col=10,.row=0};
user_input_t ui_edit_alarm_pm_am = {.col=13,.row=0};
user_input_t ui_edit_alarm_type = {.col=0,.row=1};
user_input_t ui_edit_alarm_enable = {.col=8,.row=1};

#ifdef	__cplusplus
extern "C" {
#endif

	static inline void f12_time_to_string(f12_hour_t *time, char *string)
	{
		sprintf(string, "%s%2.2d:%2.2d:%2.2d %s",
				string,
				time->hour,time->minute,time->second,
				hour_pm_am_str[time->pm? 1: 0]
		       );
	}

	static inline void day_to_string(uint8_t day, char* string)
	{
		sprintf(string,"%s%s",string,day_str[day-1]);
	}

	void display_numeric_input(input_numeric_t *input);
	void display_binary_input(input_binary_t *input);
	void display_time_day(time_day_t *timeday);
	void display_alarm_time(alarm_t *alarm);
	void display_alarm_days_header();
	void display_alarm_days(alarm_t *alarm);
	void display_motor_direction(motor_alarm_t *motor_alarm);
	void alarm_time_to_string(alarm_t *alarm, char *string);
	void motor_direction_to_string(motor_direction_t direction, char *string);
	void alarm_days_to_string(alarm_t *alarm, char *string);
	void mode_to_string(mode_t mode, char *string);
	void display_edit_day_alarm_screen(bool alarm1, dual_day_alarm_t *alarm);
	void display_dualday_alarm_screen(dual_day_alarm_t *alarm);
	void display_update_alarm_hour(uint8_t hour);
	void display_update_alarm_minute(uint8_t minute);
	void display_update_alarm_second(uint8_t second);
	void display_update_alarm_pm(bool pm);
	void display_update_alarm_enable(bool enable);


#ifdef	__cplusplus
}
#endif

#endif	/* DISPLAY_UTILS_H */

