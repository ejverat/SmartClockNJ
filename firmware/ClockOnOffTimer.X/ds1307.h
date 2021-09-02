/* 
 * File:   ds1307.h
 * Author: evera
 *
 * Created on August 10, 2021, 1:16 AM
 */

#ifndef DS1307_H
#define	DS1307_H

#define DS1307_I2C_ADD 0x68
#define DS1307_MEM_SIZE 64
#define DS1307_RAM_SIZE 56

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>
#include "i2c_bus.h"

typedef enum 
{
	ds1307_addrs_seconds = 0x00,
	ds1307_addrs_minutes,
	ds1307_addrs_hours,
	ds1307_addrs_day,
	ds1307_addrs_date,
	ds1307_addrs_month,
	ds1307_addrs_year,
	ds1307_addrs_control,
	ds1307_addrs_ram,
}ds1307_addrs_t;

typedef union 
{
	struct
	{
		uint8_t units 	:4;
		uint8_t tens 	:3;
		uint8_t ch 	:1;
	};
}
ds1307_seconds_t;

typedef union 
{
	struct
	{
		uint8_t units 	:4;
		uint8_t tens 	:3;
	};
}
ds1307_minutes_t;

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
ds1307_hours_t;

typedef union 
{
	struct
	{
		uint8_t day 	:3;
	};
} ds1307_day_t;

typedef union 
{
	struct
	{
		uint8_t units 	:4;
		uint8_t tens 	:2;
	};
} ds1307_date_t;

typedef union 
{
	struct
	{
		uint8_t units 	:4;
		uint8_t tens 	:1;
	};
} ds1307_month_t;

typedef union 
{
	struct
	{
		uint8_t units 	:4;
		uint8_t tens 	:4;
	};
} ds1307_year_t;

typedef union 
{
	struct
	{
		uint8_t RS0 	:1;
		uint8_t RS1 	:1;
		uint8_t :1;
		uint8_t :1;
		uint8_t SQWE 	:1;
		uint8_t :1;
		uint8_t :1;
		uint8_t OUT 	:1;
	};
} ds1307_control_t;

typedef union
{
	struct 
	{
		ds1307_seconds_t seconds;
		ds1307_minutes_t minutes;
		ds1307_hours_t hours;
		ds1307_day_t day;
		ds1307_date_t date;
		ds1307_month_t month;
		ds1307_year_t year;
		ds1307_control_t control;
		uint8_t dev_ram[DS1307_RAM_SIZE];
	};
	uint8_t bytes[DS1307_MEM_SIZE];
} ds1307_memory_map_t;

typedef struct
{
	i2c_bus_t *bus;
	ds1307_memory_map_t data;
} ds1307_t;

void ds1307_read_all(ds1307_t *dev);
uint8_t ds1307_get_seconds(ds1307_t *dev);
uint8_t ds1307_get_minutes(ds1307_t *dev);
uint8_t ds1307_get_hours(ds1307_t *dev);
uint8_t ds1307_get_day(ds1307_t *dev);
uint8_t ds1307_get_date(ds1307_t *dev);
uint8_t ds1307_get_month(ds1307_t *dev);
uint8_t ds1307_get_year(ds1307_t *dev);
void ds1307_set_seconds(ds1307_t *dev,uint8_t seconds);
void ds1307_set_minutes(ds1307_t *dev,uint8_t minutes);
void ds1307_set_hours_f24(ds1307_t *dev,uint8_t hours);
void ds1307_set_hours_f12(ds1307_t *dev,uint8_t hours, bool pm);
void ds1307_set_day(ds1307_t *dev,uint8_t day);
void ds1307_set_date(ds1307_t *dev,uint8_t date);
void ds1307_set_month(ds1307_t *dev,uint8_t month);
void ds1307_set_year(ds1307_t *dev,uint8_t year);

#ifdef	__cplusplus
}
#endif

#endif	/* DS1307_H */

