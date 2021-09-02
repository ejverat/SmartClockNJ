/* 
 * File:   ds3231.h
 * Author: evera
 *
 * Created on July 13, 2021, 4:04 AM
 */

#ifndef DS3231_H
#define	DS3231_H

#include <inttypes.h>
#include <stdio.h>
#include <stdbool.h>

#ifdef	__cplusplus
extern "C" {
#endif
#define DS3231_I2C_ADD 0x68
typedef enum {ds3231_add_seconds = 0x00, ds3231_add_minutes = 0x01, ds3231_add_hours = 0x02,
		ds3231_add_day = 0x03, ds3231_add_date, ds3231_add_month_century,
		ds3231_add_year, ds3231_add_alarm1_seconds, ds3231_add_alarm1_minutes,
		ds3231_add_alarm1_hours, ds3231_add_alarm1_day, ds3231_add_alarm1_date,
		ds3231_add_alarm2_minutes, ds3231_add_alarm2_hours, ds3231_add_alarm2_day,
		ds3231_add_alarm2_date, ds3231_add_control, ds3231_add_control_status,
		ds3231_add_aging_offset, ds3231_add_msb_temp, ds3231_add_lsb_temp} ds3231_add_t;


typedef union 
{
	struct
	{
		uint8_t units 	:4;
		uint8_t tens 	:3;
	};
}
ds3231_seconds_t;

typedef union 
{
	struct
	{
		uint8_t units 	:4;
		uint8_t tens 	:3;
	};
}
ds3231_minutes_t;

typedef union 
{
	struct
	{
		uint8_t units 	:4;
		uint8_t tens 	:1;
		uint8_t 	:1;
		uint8_t f12_24 :1;
	};
	struct 
	{
		uint8_t 	:5;
		uint8_t twenties:1;
	};
	struct 
	{
		uint8_t 	:5;
		uint8_t am_pm 	:1;
	};
}
ds3231_hours_t;

typedef union 
{
	struct
	{
		uint8_t day 	:3;
	};
} ds3231_day_t;

typedef union 
{
	struct
	{
		uint8_t units 	:4;
		uint8_t tens 	:2;
	};
} ds3231_date_t;

typedef union 
{
	struct
	{
		uint8_t units 	:4;
		uint8_t tens 	:1;
		uint8_t 	:2;
		uint8_t century:1;
	};
} ds3231_month_t;

typedef union 
{
	struct
	{
		uint8_t units 	:4;
		uint8_t tens 	:4;
	};
} ds3231_year_t;

typedef union 
{
	struct
	{
		uint8_t units 	:4;
		uint8_t tens 	:3;
		uint8_t M1 	:1;
	};
}
ds3231_alarm_seconds_t;

typedef union 
{
	struct
	{
		uint8_t units 	:4;
		uint8_t tens 	:3;
		uint8_t M2 	:1;
	};
}
ds3231_alarm_minutes_t;

typedef union 
{
	struct
	{
		uint8_t units 	:4;
		uint8_t tens 	:1;
		uint8_t 	:1;
		uint8_t f12_24 :1;
		uint8_t M3 	:1;
	};
	struct 
	{
		uint8_t 	:5;
		uint8_t twenties:1;
	};
	struct 
	{
		uint8_t 	:5;
		uint8_t am_pm 	:1;
	};
}
ds3231_alarm_hours_t;

typedef union 
{
	struct
	{
		uint8_t  	:6;
		uint8_t DY_DT 	:1;
		uint8_t M4 	:1;
	};
	struct
	{
		uint8_t day 	:4;
	};
	struct
	{
		uint8_t date_units 	:4;
		uint8_t date_tens 	:2;
	};
} ds3231_alarm_day_date_t;

typedef union 
{
	struct
	{
		uint8_t A1IE 	:1;
		uint8_t A2IE 	:1;
		uint8_t INTCN 	:1;
		uint8_t RS 	:2;
		uint8_t CONV 	:1;
		uint8_t BBSQW 	:1;
		uint8_t EOSC 	:1;
	};
	struct
	{
		uint8_t 	:3;
		uint8_t RS1 	:1;
		uint8_t RS2 	:1;
	};
} ds3231_control_t;

typedef union 
{
	struct
	{
		uint8_t A1F 		:1;
		uint8_t A2F 		:1;
		uint8_t BSY 		:1;
		uint8_t EN32KHZ 	:2;
		uint8_t  		:3;
		uint8_t OSF 		:1;
	};
	struct
	{
		uint8_t 	:3;
		uint8_t RS1 	:1;
		uint8_t RS2 	:1;
	};
} ds3231_control_status_t;

typedef union
{
	struct
	{
		uint8_t data:7;
		uint8_t sign:1;
	};
}ds3231_aging_offset_t;

typedef union
{
	struct
	{
		uint8_t data:7;
		uint8_t sign:1;
	};
}ds3231_temp_msb_t;

typedef union
{
	struct
	{
		uint8_t     :6;
		uint8_t data:2;
	};
}ds3231_temp_lsb_t;

typedef union
{
	struct 
	{
		ds3231_seconds_t seconds;
		ds3231_minutes_t minutes;
		ds3231_hours_t hours;
		ds3231_day_t day;
		ds3231_date_t date;
		ds3231_month_t month;
		ds3231_year_t year;
		struct
		{
			ds3231_alarm_seconds_t seconds;
			ds3231_alarm_minutes_t minutes;
			ds3231_alarm_hours_t hours;
			ds3231_alarm_day_date_t day_date;
		} alarm1;
		struct
		{
			ds3231_alarm_minutes_t minutes;
			ds3231_alarm_hours_t hours;
			ds3231_alarm_day_date_t day_date;
		} alarm2;
		ds3231_control_t control;
		ds3231_control_status_t control_status;
		ds3231_aging_offset_t aging_offset;
		ds3231_temp_msb_t temp_msb;
		ds3231_temp_lsb_t temp_lsb;
	};
	uint8_t bytes[19];
} ds3231_memory_map_t;

typedef struct
{
	void (*start_fn) (uint8_t);
	void (*stop_fn) (void);
	void (*read_fn) (uint8_t*,size_t);
	void (*write_fn)(uint8_t*,size_t);
	ds3231_memory_map_t data;
} ds3231_t;

void ds3231_read_all(ds3231_t *dev);
uint8_t ds3231_get_seconds(ds3231_t *dev);
uint8_t ds3231_get_minutes(ds3231_t *dev);
uint8_t ds3231_get_hours(ds3231_t *dev);
uint8_t ds3231_get_day(ds3231_t *dev);
uint8_t ds3231_get_date(ds3231_t *dev);
uint8_t ds3231_get_month(ds3231_t *dev);
uint8_t ds3231_get_year(ds3231_t *dev);
void ds3231_set_seconds(ds3231_t *dev,uint8_t seconds);
void ds3231_set_minutes(ds3231_t *dev,uint8_t minutes);
void ds3231_set_hours_f24(ds3231_t *dev,uint8_t hours);
void ds3231_set_hours_f12(ds3231_t *dev,uint8_t hours, bool pm);
void ds3231_set_day(ds3231_t *dev,uint8_t day);
void ds3231_set_date(ds3231_t *dev,uint8_t date);
void ds3231_set_month(ds3231_t *dev,uint8_t month);
void ds3231_set_year(ds3231_t *dev,uint8_t year);

#ifdef	__cplusplus
}
#endif

#endif	/* DS3231_H */

