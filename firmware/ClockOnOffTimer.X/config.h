/* 
 * File:   config.h
 * Author: evera
 *
 * Created on July 10, 2021, 3:03 AM
 */

#ifndef CONFIG_H
#define	CONFIG_H

#include <stdbool.h>

#include "text_display.h"
#include "motor.h"
#include "smart_pir.h"
#include "dual_day_alarm.h"

#define PIR_MINIMUM_INACTIVE_TIME 1000*60*5
#define SLEEP_TIMEOUT_MS 5000


//#define USE_DS3231
#define USE_DS1307

#if !defined (USE_DS1307) && !defined (USE_DS3231)
#define USE_DS1307
#endif

#if defined (USE_DS1307)
#include "ds1307.h"
#elif defined (USE_DS3231)
#include "ds3231.h"
#endif

#ifdef	__cplusplus
extern "C" {
#endif
	void config_devices();
	text_display_t *get_text_display();
#if defined (USE_DS3231)
	ds3231_t *get_ds3231();
#elif defined (USE_DS1307)
	ds1307_t *get_ds1307();
#endif
	motor_t *get_motor();
	smart_pir_t *get_pir();
	dual_day_alarm_t *get_dualday_alarms();
	bool is_alarm_mode();
	bool is_pir_mode();
	void set_to_pir_mode();
	void set_to_alarm_mode();

#ifdef	__cplusplus
}
#endif

#endif	/* CONFIG_H */
