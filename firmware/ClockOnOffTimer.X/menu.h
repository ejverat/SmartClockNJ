/* 
 * File:   menu.h
 * Author: evera
 *
 * Created on July 16, 2021, 4:33 AM
 */

#ifndef MENU_H
#define	MENU_H

#include <stdbool.h>

#include "time_day.h"
#include "motor_alarm.h"

#ifdef	__cplusplus
extern "C" {
#endif
	typedef struct 
	{
		uint32_t timeout_ms;
		void (*refresh)(void);
		void (*on_ok)(void);
		void (*on_inc)(void);
		void (*on_dec)(void);
		void (*on_timeout)(void);
	} menu_t;

	menu_t *get_current_menu();
	void init_menus();
	void menu_sleep();


#ifdef	__cplusplus
}
#endif

#endif	/* MENU_H */

