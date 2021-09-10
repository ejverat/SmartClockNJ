#include <string.h>
#include <stdbool.h>

#include "menu.h"
#include "sys_time.h"
#include "config.h"
#include "text_display.h"
#include "display_utils.h"
#include "time_day_utils.h"
#include "time_day.h"
#include "button.h"
#include "clock.h"
#include "alarm_utils.h"
#include "motor_utils.h"

#define TIMEOUT_DISPLAY 1000
#define TIMEOUT_INACTIVITY 10000

static const uint32_t max_timeout_value = 4294967295;

static bool sleep_enabled;
static uint32_t spin_time;

static menu_t *current_menu;
static menu_t m_current_time;
static menu_t m_edit_time_q;
static menu_t m_edit_time;
static menu_t m_alarm_list;
static menu_t m_current_pir_status;
static menu_t m_sleep;
static menu_t m_change_mode_q;
static menu_t m_change_mode;
static menu_t m_list_alarms_q;
static menu_t m_edit_on_alarm_q;
static menu_t m_edit_off_alarm_q;
static menu_t m_edit_on_alarm;
static menu_t m_edit_off_alarm;
static menu_t m_current_manual_status;
static menu_t m_move_motor_q;
static menu_t m_move_motor;
static menu_t m_change_spin_time_q;
static menu_t m_change_spin_time;

typedef enum 
{
	time_day_field_day, time_day_field_hour, time_day_field_minute, time_day_field_second, 
	time_day_field_am_pm
} time_day_field_t;

typedef enum 
{
	motor_alarm_field_hour, motor_alarm_field_minute, motor_alarm_field_second, 
	motor_alarm_field_am_pm, motor_alarm_field_direction, motor_alarm_field_day
} motor_alarm_field_t;

typedef enum 
{
	dual_alarm_field_hour, 
	dual_alarm_field_minute, 
	dual_alarm_field_second, 
	dual_alarm_field_am_pm, 
	dual_alarm_field_enable 
} dual_alarm_field_t;

static time_day_t *timeday_ptr;
static time_day_t timeday_tmp;
static time_day_field_t current_time_day_field;

static motor_alarm_t *motor_alarm_ptr;
static motor_alarm_field_t current_motor_alarm_field;
static uint8_t current_field_day_idx;

static dual_day_alarm_t *dual_alarm_ptr;
static day_alarm_t *day_alarm_ptr;
static dual_alarm_field_t dual_alarm_field;
static void (*callback_fn) (void);
static mode_t selected_mode;

const char edit_time_title[] = "ED. TIME(+,ok,-)";
static void display_edit_time_q();
static void display_edit_time();
static void edit_timeday_next_field();
static void edit_timeday_inc_field();
static void edit_timeday_dec_field();
static void edit_alarm_dec_field();
static void edit_alarm_inc_field();
static void display_edit_alarms_q();
static void display_edit_current_alarm_q();
static void display_add_alarm_q();
static void display_alarm_delete_q();
static void display_add_alarm();
static void display_alarm_info();
static void display_change_to_alarm_mode_q();
static void display_change_to_pir_mode_q();
static void display_list_alarms_q();
static void display_dualday_alarm();
static void display_on_alarm_q();
static void display_off_alarm_q();
static void display_edit_on_alarm();
static void display_edit_off_alarm();
static void display_change_mode_q();
static void display_change_mode();
static void display_manual_status();
static void display_move_motor_q();
static void display_move_motor();
static void display_change_spin_time_q();
static void display_change_spin_time();
static void go_to_current_time();
static void go_to_pir_status();
static void go_to_pir_mode();
static void go_to_edit_time_q();
static void go_to_change_mode_q();
static void go_to_change_mode();
static void go_to_update_mode();
static void go_prev_mode();
static void go_next_mode();
static void go_to_alarm_mode_q();
static void go_to_list_alarms_q();
static void go_to_list_alarms();
static void go_to_edit_on_alarm_q();
static void go_to_edit_off_alarm_q();
static void go_to_prev_dualday_alarm();
static void go_to_next_dualday_alarm();
static void go_to_edit_on_alarm();
static void go_to_edit_off_alarm();
static void go_to_next_dualday_alarm_field();
static void go_to_move_motor_q();
static void go_to_move_motor();
static void go_to_change_spin_time_q();
static void go_to_spin_left_motor();
static void go_to_spin_right_motor();
static void go_to_change_spin_time();
static void update_spin_time();
static void dec_spin_time();
static void inc_spin_time();
static void dec_dualday_alarm_field();
static void inc_dualday_alarm_field();
static void change_mode();
static void toggle_mode();
static void go_to_edit_time();
static void display_current_timeday();
static void display_current_pir_status();
static void do_nothing();
static void go_to_home();
static void go_to_sleep();
static void go_to_wake();
static void motor_spin_to_left();
static void motor_spin_to_right();

menu_t *get_current_menu()
{
	return current_menu;
}

/**
 * PIR MODE (PIR status) [Change to Alarm Mode]
 *
 * menu 			LEFT Action 		RIGHT Action 		OK Action
 * Pir Status 			Change to Alarm Mode Q	Change to Alarm Mode Q 	X
 * Change to Alarm Mode Q 	X 			X 			Change to Alarm Mode
 *
 *
 * ALARM MODE (Current time) [Edit Time Q -> List Alarms Q -> Change to PIR Mode]
 *
 * Current Time 		Change to PIR Mode Q	Edit Time Q 		X
 * Change to PIR Mode Q		List Alarms Q 		Edit Time Q 		Change to PIR Mode
 * Edit Time Q 			Change to PIR Mode Q 	List Alarms Q 		Edit Time
 * List Alarms Q 	 	Edit Time Q 		Change to PIR Mode      List Alarms
 * Edit Time 			Decrease Time Field	Increase Time Field	Next Time Field
 * List Alarms 			Previous Alarm 		Next Alarm 		Edit Alarm to ON Q
 * Decrease Time Field 		Decrease Time Field 	Increase Time Field 	Next Time Field
 * Increase Time Field 		Decrease Time Field 	Increase Time Field 	Next Time Field
 * On Last Time Field 		Decrease Time Field 	Increase Time Field 	Current Time
 * Edit Alarm to ON Q 		Edit Alarm to OFF Q 	Edit Alarm to OFF Q 	Edit ON Alarm
 * Edit Alarm To OFF Q 		Edit Alarm to ON Q 	Edit Alarm to ON Q 	Edit OFF Alarm
 * Edit ON Alarm 		Decrease Alarm Field 	Increase Alarm Field 	Next Alarm Field
 * Edit OFF Alarm 		Decrease Alarm Field 	Increase Alarm Field 	Next Alarm Field
 */
void init_menus()
{
	sleep_enabled = true;
	spin_time = get_time_to_spin();

	/* Menu config for pir mode*/

	current_menu = &m_current_pir_status;
	selected_mode = PIR_MODE;

	m_current_pir_status.refresh = display_current_pir_status;
	//m_current_pir_status.on_ok = do_nothing;
	m_current_pir_status.on_ok = display_current_pir_status;
	m_current_pir_status.on_dec = go_to_change_mode_q;
	m_current_pir_status.on_inc = go_to_change_mode_q;
	m_current_pir_status.on_timeout = go_to_wake;
	m_current_pir_status.timeout_ms = TIMEOUT_DISPLAY;

	m_change_mode_q.refresh = display_change_mode_q;
	m_change_mode_q.on_ok = go_to_change_mode;
	m_change_mode_q.on_dec = do_nothing;
	m_change_mode_q.on_inc = do_nothing;
	m_change_mode_q.on_timeout = go_to_home;
	m_change_mode_q.timeout_ms = TIMEOUT_INACTIVITY;

	m_change_mode.refresh = display_change_mode;
	m_change_mode.on_ok = go_to_update_mode;
	m_change_mode.on_dec = go_prev_mode;
	m_change_mode.on_inc = go_next_mode;
	m_change_mode.on_timeout = do_nothing;
	m_change_mode.timeout_ms = max_timeout_value;

	/* Menu config for alarm mode*/

	m_current_time.refresh = display_current_timeday;
	//m_current_time.on_ok = do_nothing;
	m_current_time.on_ok = display_current_timeday;
	m_current_time.on_dec = go_to_change_mode_q;
	m_current_time.on_inc = go_to_edit_time_q;
	m_current_time.on_timeout = go_to_wake;
	m_current_time.timeout_ms = TIMEOUT_DISPLAY;

	m_edit_time_q.refresh = display_edit_time_q;
	m_edit_time_q.on_ok = go_to_edit_time;
	m_edit_time_q.on_dec = go_to_change_mode_q;
	m_edit_time_q.on_inc = go_to_list_alarms_q;
	m_edit_time_q.on_timeout = go_to_home;
	m_edit_time_q.timeout_ms = TIMEOUT_INACTIVITY;

	/* List Alarms Q 	 	Edit Time Q 		Change to PIR Mode      List Alarms*/
	m_list_alarms_q.refresh = display_list_alarms_q;
	m_list_alarms_q.on_ok = go_to_list_alarms;
	m_list_alarms_q.on_dec = go_to_edit_time_q;
	m_list_alarms_q.on_inc = go_to_change_mode_q;
	m_list_alarms_q.on_timeout = go_to_home;
	m_list_alarms_q.timeout_ms = TIMEOUT_INACTIVITY;

	/* Edit Time 			Decrease Time Field	Increase Time Field	Next Time Field*/
	m_edit_time.refresh = display_edit_time;
	m_edit_time.on_ok = edit_timeday_next_field;
	m_edit_time.on_inc = edit_timeday_inc_field;
	m_edit_time.on_dec = edit_timeday_dec_field;
	m_edit_time.on_timeout = do_nothing;
	m_edit_time.timeout_ms = max_timeout_value; //max uint32_t value;

	/* List Alarms 			Previous Alarm 		Next Alarm 		Edit Alarm to ON Q*/
	m_alarm_list.refresh = display_dualday_alarm;
	m_alarm_list.on_ok = go_to_edit_on_alarm_q;
	m_alarm_list.on_dec = go_to_prev_dualday_alarm;
	m_alarm_list.on_inc = go_to_next_dualday_alarm;
	m_alarm_list.on_timeout = go_to_home;
	m_alarm_list.timeout_ms = TIMEOUT_INACTIVITY;
	m_alarm_list.refresh = display_dualday_alarm;

	/* Edit Alarm to ON Q 		Edit Alarm to OFF Q 	Edit Alarm to OFF Q 	Edit ON Alarm*/
	m_edit_on_alarm_q.refresh = display_on_alarm_q;
	m_edit_on_alarm_q.on_ok = go_to_edit_on_alarm;
	m_edit_on_alarm_q.on_dec = go_to_edit_off_alarm_q;
	m_edit_on_alarm_q.on_inc = go_to_edit_off_alarm_q;
	m_edit_on_alarm_q.on_timeout = go_to_home;
	m_edit_on_alarm_q.timeout_ms = TIMEOUT_INACTIVITY;

	/* Edit Alarm To OFF Q 		Edit Alarm to ON Q 	Edit Alarm to ON Q 	Edit OFF Alarm*/
	m_edit_off_alarm_q.refresh = display_off_alarm_q;
	m_edit_off_alarm_q.on_ok = go_to_edit_off_alarm;
	m_edit_off_alarm_q.on_dec = go_to_edit_on_alarm_q;
	m_edit_off_alarm_q.on_inc = go_to_edit_on_alarm_q;
	m_edit_off_alarm_q.on_timeout = go_to_home;
	m_edit_off_alarm_q.timeout_ms = TIMEOUT_INACTIVITY;

	/* Edit ON Alarm 		Decrease Alarm Field 	Increase Alarm Field 	Next Alarm Field*/
	m_edit_on_alarm.refresh = display_edit_on_alarm;
	m_edit_on_alarm.on_ok = go_to_next_dualday_alarm_field;
	m_edit_on_alarm.on_dec = dec_dualday_alarm_field;
	m_edit_on_alarm.on_inc = inc_dualday_alarm_field;
	m_edit_on_alarm.on_timeout = do_nothing;
	m_edit_on_alarm.timeout_ms = max_timeout_value;

	/* Edit OFF Alarm 		Decrease Alarm Field 	Increase Alarm Field 	Next Alarm Field*/
	m_edit_off_alarm.refresh = display_edit_off_alarm;
	m_edit_off_alarm.on_ok = go_to_next_dualday_alarm_field;
	m_edit_off_alarm.on_dec = dec_dualday_alarm_field;
	m_edit_off_alarm.on_inc = inc_dualday_alarm_field;
	m_edit_off_alarm.on_timeout = do_nothing;
	m_edit_off_alarm.timeout_ms = max_timeout_value;

	/* Menu config for Manual mode */
	m_current_manual_status.refresh = display_manual_status;
	m_current_manual_status.on_ok = go_to_change_mode_q;
	m_current_manual_status.on_dec = go_to_spin_left_motor;
	m_current_manual_status.on_inc = go_to_spin_right_motor;
	m_current_manual_status.on_timeout = do_nothing;
	m_current_manual_status.timeout_ms = max_timeout_value;

	m_move_motor_q.refresh = display_move_motor_q;
	m_move_motor_q.on_ok = go_to_move_motor;
	m_move_motor_q.on_dec = go_to_change_mode_q;
	m_move_motor_q.on_inc = go_to_change_spin_time_q;
	m_move_motor_q.on_timeout = go_to_home;
	m_move_motor_q.timeout_ms = TIMEOUT_INACTIVITY;

	m_move_motor.refresh = display_move_motor;
	m_move_motor.on_ok = go_to_home;
	m_move_motor.on_dec = go_to_spin_left_motor;
	m_move_motor.on_inc = go_to_spin_right_motor;
	m_move_motor.on_timeout = display_move_motor;
	m_move_motor.timeout_ms = TIMEOUT_DISPLAY;

	m_change_spin_time_q.refresh = display_change_spin_time_q;
	m_change_spin_time_q.on_ok = go_to_change_spin_time;
	m_change_spin_time_q.on_dec = go_to_move_motor_q;
	m_change_spin_time_q.on_inc = go_to_change_mode_q;
	m_change_spin_time_q.on_timeout = go_to_home;
	m_change_spin_time_q.timeout_ms = TIMEOUT_INACTIVITY;

	m_change_spin_time.refresh = display_change_spin_time;
	m_change_spin_time.on_ok = update_spin_time;
	m_change_spin_time.on_dec = dec_spin_time;
	m_change_spin_time.on_inc = inc_spin_time;
	m_change_spin_time.on_timeout = do_nothing;
	m_change_spin_time.timeout_ms = max_timeout_value;

	m_sleep.refresh = do_nothing;
	m_sleep.on_ok = go_to_wake;
	m_sleep.on_inc = go_to_wake;
	m_sleep.on_dec = go_to_wake;
	m_sleep.on_timeout = do_nothing;
	m_sleep.timeout_ms = max_timeout_value;
}

void menu_sleep()
{
	if (current_menu != &m_sleep && sleep_enabled)
	{
		go_to_sleep();
	}
}

static void display_edit_time_q()
{
	text_display_t *display = get_text_display();
	display_clear(display);
	display_set_cursor(display,0,0);
	display_cursor_off(display);
	display_blink_off(display);
	display_print_text(display,"EDIT TIME?");
	display_set_cursor(display,0,0);
	display_set_cursor(display, 0, 1);
	display_print_text(display,"(-,ok,+)");
}

static void display_edit_time()
{
	text_display_t *display = get_text_display();
	//display text
	display_set_cursor(display, 0, 0);
	display_print_text(display, "ED. TIME(+,ok,-)");
	display_set_cursor(display, 0, 1);
	display_time_day(timeday_ptr);

	//enable cursor and blink
	display_cursor_on(display);
	display_blink_on(display);

	uint8_t cursor_pos = 0;

	switch(current_time_day_field)
	{
		case time_day_field_day:
			cursor_pos = 0;
			break;
		case time_day_field_hour:
			cursor_pos = 4;
			break;
		case time_day_field_minute:
			cursor_pos = 7;
			break;
		case time_day_field_second:
			cursor_pos = 10;
			break;
		case time_day_field_am_pm:
			cursor_pos = 13;
			break;
	}

	display_set_cursor(display, cursor_pos, 1);
}
static void edit_timeday_next_field()
{
	if (current_time_day_field == time_day_field_am_pm)
	{
		set_timeday_rtc(timeday_ptr);
		go_to_home();
	}
	else
	{
		current_time_day_field++;
		current_menu->refresh();
	}
}

static void edit_timeday_inc_field()
{
	switch(current_time_day_field)
	{
		case time_day_field_day:
			timeday_ptr->day_of_week = roll_inc_day_of_week(timeday_ptr->day_of_week);
			break;
		case time_day_field_hour:
			timeday_ptr->hour = roll_inc_hour_f12(timeday_ptr->hour);
			break;
		case time_day_field_minute:
			timeday_ptr->minute = roll_inc_minute(timeday_ptr->minute);
			break;
		case time_day_field_second:
			timeday_ptr->second = roll_inc_second(timeday_ptr->second);
			break;
		case time_day_field_am_pm:
			timeday_ptr->pm = !timeday_ptr->pm;
			break;
	}
	current_menu->refresh();
}

static void edit_timeday_dec_field()
{
	switch(current_time_day_field)
	{
		case time_day_field_day:
			timeday_ptr->day_of_week = roll_dec_day_of_week(timeday_ptr->day_of_week);
			break;
		case time_day_field_hour:
			timeday_ptr->hour = roll_dec_hour_f12(timeday_ptr->hour);
			break;
		case time_day_field_minute:
			timeday_ptr->minute = roll_dec_minute(timeday_ptr->minute);
			break;
		case time_day_field_second:
			timeday_ptr->second = roll_dec_second(timeday_ptr->second);
			break;
		case time_day_field_am_pm:
			timeday_ptr->pm = !timeday_ptr->pm;
			break;
	}
	current_menu->refresh();
}

static void edit_alarm_dec_field()
{
	switch (current_motor_alarm_field)
	{
		case motor_alarm_field_hour:
			motor_alarm_ptr->alarm.time.hour = roll_dec_hour_f12(motor_alarm_ptr->alarm.time.hour);
			break;
		case motor_alarm_field_minute:
			motor_alarm_ptr->alarm.time.minute = roll_dec_minute(motor_alarm_ptr->alarm.time.minute);
			break;
		case motor_alarm_field_second:
			motor_alarm_ptr->alarm.time.second = roll_dec_second(motor_alarm_ptr->alarm.time.second);
			break;
		case motor_alarm_field_am_pm:
			motor_alarm_ptr->alarm.time.pm = !motor_alarm_ptr->alarm.time.pm;
			break;
		case motor_alarm_field_direction:
			motor_alarm_ptr->direction = motor_alarm_ptr->direction == RIGHT? LEFT : RIGHT;
			break;
		case motor_alarm_field_day:
			motor_alarm_ptr->alarm.days[current_field_day_idx] = !motor_alarm_ptr->alarm.days[current_field_day_idx];
			break;
	}
	current_menu->refresh();

}

static void edit_alarm_inc_field()
{
	switch (current_motor_alarm_field)
	{
		case motor_alarm_field_hour:
			motor_alarm_ptr->alarm.time.hour = roll_inc_hour_f12(motor_alarm_ptr->alarm.time.hour);
			break;
		case motor_alarm_field_minute:
			motor_alarm_ptr->alarm.time.minute = roll_inc_minute(motor_alarm_ptr->alarm.time.minute);
			break;
		case motor_alarm_field_second:
			motor_alarm_ptr->alarm.time.second = roll_inc_second(motor_alarm_ptr->alarm.time.second);
			break;
		case motor_alarm_field_am_pm:
			motor_alarm_ptr->alarm.time.pm = !motor_alarm_ptr->alarm.time.pm;
			break;
		case motor_alarm_field_direction:
			motor_alarm_ptr->direction = motor_alarm_ptr->direction == RIGHT? LEFT : RIGHT;
			break;
		case motor_alarm_field_day:
			motor_alarm_ptr->alarm.days[current_field_day_idx] = !motor_alarm_ptr->alarm.days[current_field_day_idx];
			break;
	}
	current_menu->refresh();
}

static void display_edit_alarms_q()
{
	text_display_t *display = get_text_display();
	display_clear(display);
	display_set_cursor(display,0,0);
	display_cursor_off(display);
	display_blink_off(display);
	display_print_text(display,"EDIT ALARMS?");
	display_set_cursor(display,0,0);
	display_set_cursor(display, 0, 1);
	display_print_text(display,"(-,ok,+)");
}

static void display_edit_current_alarm_q()
{
	text_display_t *display = get_text_display();
	display_clear(display);
	display_set_cursor(display,0,0);
	display_cursor_off(display);
	display_blink_off(display);
	display_print_text(display,"EDIT ALARM?");
	display_set_cursor(display,0,0);
	display_set_cursor(display, 0, 1);
	display_print_text(display,"(-,ok,+)");
}

static void display_add_alarm_q()
{
	text_display_t *display = get_text_display();
	display_clear(display);
	display_set_cursor(display,0,0);
	display_cursor_off(display);
	display_blink_off(display);
	display_print_text(display,"ADD ALARM?");
	display_set_cursor(display,0,0);
	display_set_cursor(display, 0, 1);
	display_print_text(display,"(-,ok,+)");
}

static void display_alarm_delete_q()
{
	text_display_t *display = get_text_display();
	display_clear(display);
	display_set_cursor(display,0,0);
	display_cursor_off(display);
	display_blink_off(display);
	display_print_text(display,"DELETE ALARM?");
	display_set_cursor(display,0,0);
	display_set_cursor(display, 0, 1);
	display_print_text(display,"(-,ok,+)");
}

static void display_add_alarm()
{
	text_display_t *display = get_text_display();

	display_clear(display);
	display_set_cursor(display,0,0);
	display_cursor_on(display);
	display_blink_on(display);

	char text[17];

	memset(text,'\0',17);
	alarm_time_to_string(&motor_alarm_ptr->alarm, text);
	display_print_text(display, text);
	display_print_text(display, " ");

	memset(text,'\0',17);
	motor_direction_to_string(motor_alarm_ptr->direction, text);
	display_print_text(display, text);


	display_set_cursor(display,0,1);

	memset(text,'\0',17);
	alarm_days_to_string(&motor_alarm_ptr->alarm, text);
	display_print_text(display, text);
	uint8_t cursor_row;
	uint8_t cursor_col;

	switch (current_motor_alarm_field)
	{
		case motor_alarm_field_hour:
			cursor_col = 0;
			cursor_row = 0;
			break;
		case motor_alarm_field_minute:
			cursor_col = 3;
			cursor_row = 0;
			break;
		case motor_alarm_field_second:
			cursor_col = 6;
			cursor_row = 0;
			break;
		case motor_alarm_field_am_pm:
			cursor_col = 9;
			cursor_row = 0;
			break;
		case motor_alarm_field_direction:
			cursor_col = 12;
			cursor_row = 0;
			break;
		case motor_alarm_field_day:
			cursor_col = current_field_day_idx*2;
			cursor_row = 1;
			break;
	}
	display_set_cursor(display,cursor_col,cursor_row);
}

static void display_alarm_info()
{
	text_display_t *display = get_text_display();
	
	display_blink_off(display);
	display_cursor_off(display);
	display_clear(display);
	display_set_cursor(display,0,0);

	char text[17];

	memset(text,'\0',17);
	alarm_time_to_string(&motor_alarm_ptr->alarm, text);
	display_print_text(display, text);
	display_print_text(display, " ");

	memset(text,'\0',17);
	motor_direction_to_string(motor_alarm_ptr->direction, text);
	display_print_text(display, text);


	display_set_cursor(display,0,1);

	memset(text,'\0',17);
	alarm_days_to_string(&motor_alarm_ptr->alarm, text);
	display_print_text(display, text);
}

static void display_change_to_alarm_mode_q()
{
	text_display_t *display = get_text_display();
	display_clear(display);
	display_set_cursor(display,0,0);
	display_cursor_off(display);
	display_blink_off(display);
	display_print_text(display,"ALARM MODE?");
	display_set_cursor(display,0,0);
	display_set_cursor(display, 0, 1);
	display_print_text(display,"(-,ok,+)");
}

static void display_change_to_pir_mode_q()
{
	text_display_t *display = get_text_display();
	display_clear(display);
	display_set_cursor(display,0,0);
	display_cursor_off(display);
	display_blink_off(display);
	display_print_text(display,"PIR MODE?");
	display_set_cursor(display,0,0);
	display_set_cursor(display, 0, 1);
	display_print_text(display,"(-,ok,+)");
}

static void display_list_alarms_q()
{
	text_display_t *display = get_text_display();
	display_clear(display);
	display_set_cursor(display,0,0);
	display_cursor_off(display);
	display_blink_off(display);
	display_print_text(display,"LIST ALARMS?");
	display_set_cursor(display,0,0);
	display_set_cursor(display, 0, 1);
	display_print_text(display,"(-,ok,+)");
}

static void display_dualday_alarm()
{
	text_display_t *display = get_text_display();
	display_set_cursor(display,0,0);
	display_cursor_off(display);
	display_blink_off(display);
	display_dualday_alarm_screen(dual_alarm_ptr);
}

static void display_on_alarm_q()
{
	text_display_t *display = get_text_display();
	display_clear(display);
	display_set_cursor(display,0,0);
	display_cursor_off(display);
	display_blink_off(display);
	display_print_text(display,"EDIT ON ALARM?");
	display_set_cursor(display,0,0);
	display_set_cursor(display, 0, 1);
	display_print_text(display,"(-,ok,+)");
}

static void display_off_alarm_q()
{
	text_display_t *display = get_text_display();
	display_clear(display);
	display_set_cursor(display,0,0);
	display_cursor_off(display);
	display_blink_off(display);
	display_print_text(display,"EDIT OFF ALARM?");
	display_set_cursor(display,0,0);
	display_set_cursor(display, 0, 1);
	display_print_text(display,"(-,ok,+)");
}

static void display_edit_on_alarm()
{
	text_display_t *display = get_text_display();
	display_set_cursor(display,0,0);
	display_edit_day_alarm_screen(true,dual_alarm_ptr);
	display_cursor_on(display);
	display_blink_on(display);
	display_update_alarm_hour(day_alarm_ptr->time.hour);
}

static void display_edit_off_alarm()
{
	text_display_t *display = get_text_display();
	display_set_cursor(display,0,0);
	display_edit_day_alarm_screen(false,dual_alarm_ptr);
	display_blink_on(display);
	display_cursor_on(display);
	display_update_alarm_hour(day_alarm_ptr->time.hour);
}

static void display_change_mode_q()
{
	text_display_t *display = get_text_display();
	display_clear(display);
	display_set_cursor(display,0,0);
	display_cursor_off(display);
	display_blink_off(display);
	display_print_text(display,"CHANGE MODE?");
	display_set_cursor(display,0,0);
	display_set_cursor(display, 0, 1);
	display_print_text(display,"(-,ok,+)");
}

static void display_change_mode()
{
	text_display_t *display = get_text_display();
	display_clear(display);
	//display text
	display_set_cursor(display, 0, 0);
	display_print_text(display, "MODE(+,ok,-)");
	display_set_cursor(display, 0, 1);

	char text[17];
	memset(text,'\0',17);
	mode_to_string(selected_mode, text);
	display_print_text(display, text);

	//enable cursor and blink
	display_cursor_on(display);
	display_blink_on(display);
	display_set_cursor(display, 0, 1);

}

static void display_manual_status()
{
	text_display_t *display = get_text_display();
	display_clear(display);
	//display text
	display_set_cursor(display, 0, 0);
	display_print_text(display, "MODE:MANUAL");
	display_set_cursor(display, 0, 1);
	display_print_text(display,"UP=ON , DOWN=OFF");
	display_cursor_off(display);
	display_blink_off(display);
}

static void display_move_motor_q()
{
	text_display_t *display = get_text_display();
	display_clear(display);
	display_set_cursor(display,0,0);
	display_cursor_off(display);
	display_blink_off(display);
	display_print_text(display,"MOVE MOTOR?");
	display_set_cursor(display,0,0);
	display_set_cursor(display, 0, 1);
	display_print_text(display,"(-,ok,+)");
}

static void display_move_motor()
{
	text_display_t *display = get_text_display();
	display_clear(display);
	//display text
	display_set_cursor(display, 0, 0);
	display_print_text(display, "MOVE(+,ok,-)");
	display_set_cursor(display, 0, 1);

	char text[17];
	memset(text,'\0',17);
	motor_t *motor = get_motor();
	motor_direction_to_string(motor->direction, text);
	display_print_text(display, text);

	//enable cursor and blink
	display_cursor_on(display);
	display_blink_on(display);
	display_set_cursor(display, 0, 1);
}

static void display_change_spin_time_q()
{
	text_display_t *display = get_text_display();
	display_clear(display);
	display_set_cursor(display,0,0);
	display_cursor_off(display);
	display_blink_off(display);
	display_print_text(display,"CHANGE SPIN T.?");
	display_set_cursor(display,0,0);
	display_set_cursor(display, 0, 1);
	display_print_text(display,"(-,ok,+)");
}

static void display_change_spin_time()
{
	text_display_t *display = get_text_display();
	display_clear(display);
	//display text
	display_set_cursor(display, 0, 0);
	display_print_text(display, "SPIN T.(+,ok,-)");
	display_set_cursor(display, 0, 1);

	char text[17];
	memset(text,'\0',17);
	sprintf(text, "%10.10d ms",spin_time);
	display_print_text(display, text);

	//enable cursor and blink
	display_cursor_on(display);
	display_blink_on(display);
	display_set_cursor(display, 0, 1);
}

static void go_to_current_time()
{
	set_mode(ALARM_MODE);
	current_menu = &m_current_time;
	current_menu->refresh();
	sleep_enabled = true;
}

static void go_to_pir_status()
{
	current_menu = &m_current_pir_status;
	current_menu->refresh();
	sleep_enabled = true;
}

static void go_to_pir_mode()
{
	/* we need to reset the pir algorithm status */
	smart_pir_t* pir = get_pir();
	if (pir->device_status)
	{
		pir->device_status = false;
		pir->status_changed = false;
	}
	set_mode(PIR_MODE);
	current_menu = &m_current_pir_status;
	current_menu->refresh();
	sleep_enabled = true;
}

static void go_to_edit_time_q()
{
	current_menu = &m_edit_time_q;
	current_menu->refresh();
	sleep_enabled = true;
}

static void go_to_list_alarms_q()
{
	current_menu = &m_list_alarms_q;
	current_menu->refresh();
	sleep_enabled = true;
}

static void go_to_list_alarms()
{
	dual_alarm_ptr = get_dualday_alarms();
	current_menu = &m_alarm_list;
	current_menu->refresh();
	sleep_enabled = true;
}

static void go_to_edit_on_alarm_q()
{
	current_menu = &m_edit_on_alarm_q;
	current_menu->refresh();
	sleep_enabled = true;
}


static void go_to_edit_off_alarm_q()
{
	current_menu = &m_edit_off_alarm_q;
	current_menu->refresh();
	sleep_enabled = true;
}

static void go_to_prev_dualday_alarm()
{
	if (dual_alarm_ptr == get_dualday_alarms())
	{
		dual_alarm_ptr = &get_dualday_alarms()[6];
	}
	else
	{
		dual_alarm_ptr--;
	}
	current_menu->refresh();
}

static void go_to_next_dualday_alarm()
{
	if (dual_alarm_ptr == &get_dualday_alarms()[6])
	{
		dual_alarm_ptr = get_dualday_alarms();
	}
	else
	{
		dual_alarm_ptr++;
	}
	current_menu->refresh();
}

static void go_to_edit_on_alarm()
{
	current_menu = &m_edit_on_alarm;
	sleep_enabled = false;

	dual_alarm_field = dual_alarm_field_hour;
	day_alarm_ptr = &dual_alarm_ptr->alarm1;
	callback_fn = motor_spin_to_right;

	current_menu->refresh();
}

static void go_to_edit_off_alarm()
{
	current_menu = &m_edit_off_alarm;
	sleep_enabled = false;

	dual_alarm_field = dual_alarm_field_hour;
	day_alarm_ptr = &dual_alarm_ptr->alarm2;
	callback_fn = motor_spin_to_left;

	current_menu->refresh();
}

static void go_to_next_dualday_alarm_field()
{
	if (dual_alarm_field < dual_alarm_field_enable)
	{
		dual_alarm_field++;
		switch (dual_alarm_field)
		{
			case dual_alarm_field_minute:
				display_update_alarm_minute(day_alarm_ptr->time.minute);
				break;
			case dual_alarm_field_second:
				display_update_alarm_second(day_alarm_ptr->time.second);
				break;
			case dual_alarm_field_am_pm:
				display_update_alarm_pm(day_alarm_ptr->time.pm);
				break;
			case dual_alarm_field_enable:
				if (day_alarm_ptr->callback_fn == NULL)
				{
					display_update_alarm_enable(false);
				}
				else
				{
					display_update_alarm_enable(true);
				}
				break;
		}
	}
	else
	{
		current_menu = &m_alarm_list;
	}
}

static void dec_dualday_alarm_field()
{
	switch (dual_alarm_field)
	{
		case dual_alarm_field_hour:
			day_alarm_ptr->time.hour = roll_dec_hour_f12(day_alarm_ptr->time.hour);
			display_update_alarm_hour(day_alarm_ptr->time.hour);
			break;
		case dual_alarm_field_minute:
			day_alarm_ptr->time.minute = roll_dec_minute(day_alarm_ptr->time.minute);
			display_update_alarm_minute(day_alarm_ptr->time.minute);
			break;
		case dual_alarm_field_second:
			day_alarm_ptr->time.second = roll_dec_second(day_alarm_ptr->time.second);
			display_update_alarm_second(day_alarm_ptr->time.second);
			break;
		case dual_alarm_field_am_pm:
			day_alarm_ptr->time.pm = !day_alarm_ptr->time.pm;
			display_update_alarm_pm(day_alarm_ptr->time.pm);
			break;
		case dual_alarm_field_enable:
			if (day_alarm_ptr->callback_fn == NULL)
			{
				day_alarm_ptr->callback_fn = callback_fn;
				display_update_alarm_enable(true);
			}
			else
			{
				day_alarm_ptr->callback_fn = NULL;
				display_update_alarm_enable(false);
			}
			break;
	}
}

static void inc_dualday_alarm_field()
{
	switch (dual_alarm_field)
	{
		case dual_alarm_field_hour:
			day_alarm_ptr->time.hour = roll_inc_hour_f12(day_alarm_ptr->time.hour);
			display_update_alarm_hour(day_alarm_ptr->time.hour);
			break;
		case dual_alarm_field_minute:
			day_alarm_ptr->time.minute = roll_inc_minute(day_alarm_ptr->time.minute);
			display_update_alarm_minute(day_alarm_ptr->time.minute);
			break;
		case dual_alarm_field_second:
			day_alarm_ptr->time.second = roll_inc_second(day_alarm_ptr->time.second);
			display_update_alarm_second(day_alarm_ptr->time.second);
			break;
		case dual_alarm_field_am_pm:
			day_alarm_ptr->time.pm = !day_alarm_ptr->time.pm;
			display_update_alarm_pm(day_alarm_ptr->time.pm);
			break;
		case dual_alarm_field_enable:
			if (day_alarm_ptr->callback_fn == NULL)
			{
				day_alarm_ptr->callback_fn = callback_fn;
				display_update_alarm_enable(true);
			}
			else
			{
				day_alarm_ptr->callback_fn = NULL;
				display_update_alarm_enable(false);
			}
			break;
	}
}

static void go_to_edit_time()
{
	current_menu = &m_edit_time;
	timeday_ptr = get_rtc_timeday();
	//copy the content to avoid modify it while editing time;
	memcpy(&timeday_tmp, timeday_ptr, sizeof(time_day_t));
	timeday_ptr = &timeday_tmp;
	current_time_day_field = time_day_field_day;
	current_menu->refresh();
	sleep_enabled = false;
}

static void go_to_change_mode_q()
{
	if (get_mode() == ALARM_MODE)
	{
		m_change_mode_q.on_dec = go_to_list_alarms_q;
		m_change_mode_q.on_inc = go_to_edit_time_q;
		sleep_enabled = true;
	}
	else if (get_mode() == PIR_MODE)
	{
		m_change_mode_q.on_dec = do_nothing;
		m_change_mode_q.on_inc = do_nothing;
		sleep_enabled = true;
	}
	else if (get_mode() == MANUAL_MODE)
	{
		m_change_mode_q.on_dec = do_nothing;
		m_change_mode_q.on_inc = do_nothing;
		sleep_enabled = false;
	}
	current_menu = &m_change_mode_q;
	current_menu->refresh();
}

static void go_to_change_mode()
{
	current_menu = &m_change_mode;
	current_menu->refresh();
	sleep_enabled = false;
}

static void go_to_update_mode()
{
	set_mode(selected_mode);
	go_to_home();
}

static void go_prev_mode()
{
	switch (selected_mode)
	{
		case PIR_MODE:
			selected_mode = MANUAL_MODE;
			break;
		case ALARM_MODE:
			selected_mode = PIR_MODE;
			break;
		case MANUAL_MODE:
			selected_mode = ALARM_MODE;
			break;
	}
	current_menu->refresh();
}

static void go_next_mode()
{
	switch (selected_mode)
	{
		case PIR_MODE:
			selected_mode = ALARM_MODE;
			break;
		case ALARM_MODE:
			selected_mode = MANUAL_MODE;
			break;
		case MANUAL_MODE:
			selected_mode = PIR_MODE;
			break;
	}
	current_menu->refresh();
}

static void display_current_timeday()
{
	text_display_t *display = get_text_display();

	display_clear(display);
	display_set_cursor(display,0,0);
	display_cursor_off(display);

	time_day_t *current_time = get_rtc_timeday();
	display_time_day(current_time);

	//also we display the current mode (PIR or ALARM)
	display_set_cursor(display,0,1);

	char text[17];
	memset(text,'\0',17);
	sprintf(text, "MODE: ");
	mode_to_string(get_mode(), &text[6]);
	display_print_text(display, text);

	//disable cursor and blink
	display_cursor_off(display);
	display_blink_off(display);
}
static void display_current_pir_status()
{
	text_display_t *display = get_text_display();

	display_clear(display);
	display_set_cursor(display,0,0);
	display_cursor_off(display);

	smart_pir_t *spir = get_pir();
	char text[17];
	memset(text,'\0',17);
	sprintf(text, "PIR:%d DEV:%d",spir->status, spir->device_status);
	display_print_text(display, text);


	//also we display the current mode (PIR or ALARM)
	display_set_cursor(display,0,1);

	memset(text,'\0',17);
	sprintf(text, "MODE: ");
	mode_to_string(get_mode(), &text[6]);
	display_print_text(display, text);

	//disable cursor and blink
	display_cursor_off(display);
	display_blink_off(display);
}

static void do_nothing()
{}

static void go_to_home()
{
	if (get_mode() == ALARM_MODE)
	{
		current_menu = &m_current_time;
		current_menu->refresh();
		sleep_enabled = true;

	}
	else if (get_mode() == PIR_MODE)
	{
		current_menu = &m_current_pir_status;
		current_menu->refresh();
		sleep_enabled = true;
	}
	else if (get_mode() == MANUAL_MODE)
	{
		current_menu = &m_current_manual_status;
		current_menu->refresh();
		sleep_enabled = false;
	}
}

static void go_to_sleep()
{
	current_menu = &m_sleep;
	text_display_t *display = get_text_display();
	display_off(display);
}

static void go_to_wake()
{
	text_display_t *display = get_text_display();
	display_on(display);
	go_to_home();
}
static void motor_spin_to_left()
{
	motor_t *motor = get_motor();
	spin_motor_left(motor);
}
static void motor_spin_to_right()
{
	motor_t *motor = get_motor();
	spin_motor_right(motor);
}

static void go_to_move_motor_q()
{
	current_menu = &m_move_motor_q;
	current_menu->refresh();
	sleep_enabled = true;
}
static void go_to_move_motor()
{
	current_menu = &m_move_motor;
	current_menu->refresh();
	sleep_enabled = false;
}

static void go_to_change_spin_time_q()
{
	current_menu = &m_change_spin_time_q;
	current_menu->refresh();
	sleep_enabled = true;
}

static void go_to_spin_left_motor()
{
	motor_spin_to_left();
	current_menu->refresh();
	sleep_enabled = false;
}

static void go_to_spin_right_motor()
{
	motor_spin_to_right();
	current_menu->refresh();
	sleep_enabled = false;
}

static void go_to_change_spin_time()
{
	spin_time = get_time_to_spin();
	current_menu =  &m_change_spin_time;
	current_menu->refresh();
	sleep_enabled = false;
}

static void update_spin_time()
{
	set_time_to_spin(spin_time);
	go_to_home();
}

static void dec_spin_time()
{
	spin_time -= 100;
	current_menu->refresh();
}

static void inc_spin_time()
{
	spin_time += 100;
	current_menu->refresh();
}
