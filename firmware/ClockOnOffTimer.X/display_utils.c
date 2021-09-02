#include <string.h>

#include "display_utils.h"
#include "user_input.h"
#include "config.h"
#include "alarm.h"


void display_numeric_input(input_numeric_t *input)
{
	char text[17];
	memset(text, '\0', sizeof(text));
	snprintf(text, sizeof(text), "%d", input->user_val);

	text_display_t *display = get_text_display();
	display_print_text(display, text);

}

void display_binary_input(input_binary_t *input)
{
	text_display_t *display = get_text_display();
	if (input->user_option1)
	{
		display_print_text(display, input->option1_str);
	}
	else
	{
		display_print_text(display, input->option2_str);
	}
}

void display_time_day(time_day_t *timeday)
{
	char text[17];
	memset(text, '\0', sizeof(text));
	uint8_t am_pm_idx = timeday->pm? 1 : 0;
	sprintf(text, "%s %2.2d:%2.2d:%2.2d %s", 
			day_str[timeday->day_of_week-1], timeday->hour, timeday->minute, 
			timeday->second, hour_pm_am_str[am_pm_idx]);

	text_display_t *display = get_text_display();
	display_print_text(display, text);
}

void display_alarm_time(alarm_t *alarm)
{
	char text[17];
	memset(text, '\0', sizeof(text));
	uint8_t am_pm_idx = alarm->time.pm? 1 : 0;
	sprintf(text, "%2.2d:%2.2d:%2.2d %s", 
			alarm->time.hour, alarm->time.minute, 
			alarm->time.second, hour_pm_am_str[am_pm_idx]);

	text_display_t *display = get_text_display();
	display_print_text(display, text);

}

void display_alarm_days_header()
{
	text_display_t *display = get_text_display();
	display_print_text(display, "S M T W T F S");
}

void display_alarm_days(alarm_t *alarm)
{
	text_display_t *display = get_text_display();

	char text[14];
	memset(text, '\0', sizeof(text));
	memset(text, ' ', 13);
	unsigned i;
	for (i = 0; i<14; i+=2)
	{
		text[i] = alarm->days[i/2]? day_enabled_str[1]:day_enabled_str[0];
	}
	display_print_text(display, text);
}

void display_motor_direction(motor_alarm_t *motor_alarm)
{
	text_display_t *display = get_text_display();

	unsigned idx_dir = 0;
	if (motor_alarm->direction == LEFT)
	{
		idx_dir = 1;
	}

	display_print_text(display, motor_direction_str[idx_dir]);
}

void alarm_time_to_string(alarm_t *alarm, char *string)
{
	uint8_t am_pm_idx = alarm->time.pm? 1 : 0;
	sprintf(string,"%2.2d:%2.2d:%2.2d %s",alarm->time.hour, alarm->time.minute, alarm->time.second,
			hour_pm_am_str[am_pm_idx]);

}

void motor_direction_to_string(motor_direction_t direction, char *string)
{
	unsigned idx_dir = 0;
	if (direction == LEFT)
	{
		idx_dir = 1;
	}

	sprintf(string,"%s", motor_direction_str[idx_dir]);
}

void alarm_days_to_string(alarm_t *alarm, char *string)
{
	unsigned idx;
	for (idx = 0; idx < 7; idx++)
	{
		char day_status = day_str[idx][0];
		if (!alarm->days[idx])
		{
			day_status = day_enabled_str[0];
		}
		string[idx*2] = day_status;
		string[idx*2+1] = ' ';
	}
	string[13] = '\0';
}

void mode_to_string(bool alarm_npir_mode, char *string)
{
	unsigned idx_dir = 0;
	if (alarm_npir_mode)
	{
		idx_dir = 1;
	}

	sprintf(string,"%s", mode_str[idx_dir]);
}

static inline void display_screen(const char screen[2][17])
{
	text_display_t *display = get_text_display();
	display_clear(display);
	display_set_cursor(display, 0, 0);
	display_print_text(display, screen[0]);
	display_set_cursor(display, 0, 1);
	display_print_text(display, screen[1]);
}

static inline void display_user_input(user_input_t *ui)
{
	text_display_t *display = get_text_display();
	display_set_cursor(display, ui->col, ui->row);
	display_print_text(display,ui->text);
	display_set_cursor(display, ui->col, ui->row);
}

static inline void time_field_to_string(uint8_t val, char *string)
{
	sprintf(string,"%2.2d",val);
}

void display_edit_day_alarm_screen(bool alarm1, dual_day_alarm_t *alarm)
{
	display_screen(screen_edit_alarm);
	text_display_t *display = get_text_display();
	day_alarm_t *a;
	uint8_t a_type_idx;
	if (alarm1)
	{
		a = &alarm->alarm1;
		a_type_idx = 0;
	}
	else
	{
		a = &alarm->alarm2;
		a_type_idx = 1;
	}
	//day of week
	ui_edit_alarm_day.text = day_str[alarm->day-1];
	display_user_input(&ui_alarm_day);
	//alarm time
	char text[3];
	memset(text, '\0', sizeof(text));
	time_field_to_string(a->time.hour, text);
	ui_edit_alarm_hour.text = text;
	display_user_input(&ui_edit_alarm_hour);
	memset(text, '\0', sizeof(text));
	time_field_to_string(a->time.minute, text);
	ui_edit_alarm_minute.text = text;
	display_user_input(&ui_edit_alarm_minute);
	memset(text, '\0', sizeof(text));
	time_field_to_string(a->time.second, text);
	ui_edit_alarm_second.text = text;
	display_user_input(&ui_edit_alarm_second);
	//am - pm
	ui_edit_alarm_pm_am.text = hour_pm_am_str[a->time.pm? 1 : 0];
	display_user_input(&ui_edit_alarm_pm_am);
	// type
	ui_edit_alarm_type.text = alarm_type_str[a_type_idx];
	display_user_input(&ui_edit_alarm_type);
	// status
	uint8_t a_status_idx;
	if (a->callback_fn == NULL)
	{
		a_status_idx = 0;
	}
	else
	{
		a_status_idx = 1;
	}
	ui_edit_alarm_enable.text = alarm_status_str[a_status_idx];
	display_user_input(&ui_edit_alarm_enable);

}
void display_update_alarm_hour(uint8_t hour)
{
	char text[3];
	memset(text, '\0', sizeof(text));
	time_field_to_string(hour, text);
	ui_edit_alarm_hour.text = text;
	display_user_input (&ui_edit_alarm_hour);
}
void display_update_alarm_minute(uint8_t minute)
{
	char text[3];
	memset(text, '\0', sizeof(text));
	time_field_to_string(minute, text);
	ui_edit_alarm_minute.text = text;
	display_user_input (&ui_edit_alarm_minute);
}

void display_update_alarm_second(uint8_t second)
{
	char text[3];
	memset(text, '\0', sizeof(text));
	time_field_to_string(second, text);
	ui_edit_alarm_second.text = text;
	display_user_input (&ui_edit_alarm_second);
}
void display_update_alarm_pm(bool pm)
{
	char text[3];
	memset(text, '\0', sizeof(text));
	ui_edit_alarm_pm_am.text = hour_pm_am_str[pm? 1 : 0];
	display_user_input(&ui_edit_alarm_pm_am);
}
void display_update_alarm_enable(bool enable)
{
	char text[3];
	memset(text, '\0', sizeof(text));
	ui_edit_alarm_enable.text = alarm_status_str[enable? 1 : 0];
	display_user_input(&ui_edit_alarm_enable);
}

void display_dualday_alarm_screen(dual_day_alarm_t *alarm)
{
	display_screen(screen_dual_alarm);
	text_display_t *display = get_text_display();
	
	// day of week
	ui_alarm_day.text = day_str[alarm->day-1];
	display_user_input(&ui_alarm_day);

	char text[3];

	// alarm hour 1
	memset(text, '\0', sizeof(text));
	time_field_to_string(alarm->alarm1.time.hour, text);
	ui_alarm_hour1.text = text;
	display_user_input(&ui_alarm_hour1);

	// alarm minute 1
	memset(text, '\0', sizeof(text));
	time_field_to_string(alarm->alarm1.time.minute, text);
	ui_alarm_minute1.text = text;
	display_user_input(&ui_alarm_minute1);

	// alarm second 1
	memset(text, '\0', sizeof(text));
	time_field_to_string(alarm->alarm1.time.second, text);
	ui_alarm_second1.text = text;
	display_user_input(&ui_alarm_second1);

	// alarm pm_am 1
	ui_alarm_pm_am1.text = hour_pm_am_str[alarm->alarm1.time.pm? 1 : 0];
	display_user_input(&ui_alarm_pm_am1);

	// alarm hour 2
	memset(text, '\0', sizeof(text));
	time_field_to_string(alarm->alarm2.time.hour, text);
	ui_alarm_hour2.text = text;
	display_user_input(&ui_alarm_hour2);

	// alarm minute 2
	memset(text, '\0', sizeof(text));
	time_field_to_string(alarm->alarm2.time.minute, text);
	ui_alarm_minute2.text = text;
	display_user_input(&ui_alarm_minute2);

	// alarm second 2
	memset(text, '\0', sizeof(text));
	time_field_to_string(alarm->alarm2.time.second, text);
	ui_alarm_second2.text = text;
	display_user_input(&ui_alarm_second2);

	// alarm pm_am 2
	ui_alarm_pm_am2.text = hour_pm_am_str[alarm->alarm2.time.pm? 1 : 0];
	display_user_input(&ui_alarm_pm_am2);

}
