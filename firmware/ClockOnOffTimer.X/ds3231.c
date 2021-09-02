#include "ds3231.h"
#include <inttypes.h>
#include <string.h>
#include <stdio.h>

uint8_t buffer[20];

static void ds3231_data_write(ds3231_t *dev,const ds3231_add_t address,uint8_t *data, size_t size)
{
	buffer[0] = (uint8_t) address;
	memcpy(&buffer[1],data,size);
	dev->start_fn(DS3231_I2C_ADD);
	dev->write_fn(buffer,size+1);
	dev->stop_fn();
}

static void ds3231_data_read(ds3231_t *dev, const ds3231_add_t address,uint8_t* data, size_t size)
{
	dev->start_fn(DS3231_I2C_ADD);
	uint8_t add = address;
	dev->write_fn(&add,1);
	dev->stop_fn();
	dev->start_fn(DS3231_I2C_ADD);
	dev->read_fn(data,size);
	dev->stop_fn();
}

void ds3231_read_all(ds3231_t *dev)
{
	ds3231_data_read(dev, ds3231_add_seconds, &dev->data.bytes[0], 19);
}
uint8_t ds3231_get_seconds(ds3231_t *dev)
{
	ds3231_data_read(dev,ds3231_add_seconds,&dev->data.seconds,1);
	return dev->data.seconds.tens*10+dev->data.seconds.units;
}
uint8_t ds3231_get_minutes(ds3231_t *dev)
{
	ds3231_data_read(dev,ds3231_add_minutes,&dev->data.minutes,1);
	return dev->data.minutes.tens*10+dev->data.minutes.units;
}
uint8_t ds3231_get_hours(ds3231_t *dev)
{
	ds3231_data_read(dev,ds3231_add_hours,&dev->data.hours,1);
	uint8_t hours;
	if (dev->data.hours.f12_24 == 0)
	{
		hours = dev->data.hours.twenties*20 + dev->data.hours.tens*10 + dev->data.hours.units;
	}
	else
	{
		hours = dev->data.hours.tens*10 + dev->data.hours.units;
	}
	return hours;
}
uint8_t ds3231_get_day(ds3231_t *dev)
{
	ds3231_data_read(dev,ds3231_add_day,&dev->data.day,1);
	return dev->data.day.day;
}
uint8_t ds3231_get_date(ds3231_t *dev)
{
	ds3231_data_read(dev,ds3231_add_date,&dev->data.date,1);
	return dev->data.date.tens*10+dev->data.date.units;
}
uint8_t ds3231_get_month(ds3231_t *dev)
{
	ds3231_data_read(dev,ds3231_add_month_century,&dev->data.month,1);
	return dev->data.month.tens*10+dev->data.month.units;
}
uint8_t ds3231_get_year(ds3231_t *dev)
{
	ds3231_data_read(dev,ds3231_add_year,&dev->data.year,1);
	return dev->data.year.tens*10+dev->data.year.units;
}
void ds3231_set_seconds(ds3231_t *dev,uint8_t seconds)
{
	dev->data.seconds.tens = seconds / 10;
	dev->data.seconds.units = seconds % 10;
	ds3231_data_write(dev,ds3231_add_seconds,&dev->data.seconds,1);
}
void ds3231_set_minutes(ds3231_t *dev,uint8_t minutes)
{
	dev->data.minutes.tens = minutes / 10;
	dev->data.minutes.units = minutes % 10;
	ds3231_data_write(dev,ds3231_add_minutes,&dev->data.minutes,1);
}
void ds3231_set_hours_f24(ds3231_t *dev,uint8_t hours)
{
	if(hours > 20)
	{
		dev->data.hours.twenties = 1;
	}
	else
	{
		dev->data.hours.tens = hours / 10;
	}
	dev->data.hours.units = hours % 10;
	dev->data.hours.f12_24 = 0;
	ds3231_data_write(dev,ds3231_add_hours,&dev->data.hours,1);
}
void ds3231_set_hours_f12(ds3231_t *dev,uint8_t hours, bool pm)
{
	if(pm)
	{
		dev->data.hours.am_pm = 1;
	}
	else
	{
		dev->data.hours.am_pm = 0;
	}
	dev->data.hours.tens = hours / 10;
	dev->data.hours.units = hours % 10;
	dev->data.hours.f12_24 = 1;
	ds3231_data_write(dev,ds3231_add_hours,&dev->data.hours,1);
}
void ds3231_set_day(ds3231_t *dev,uint8_t day)
{
	dev->data.day.day = day;
	ds3231_data_write(dev,ds3231_add_day,&dev->data.day,1);
}
void ds3231_set_date(ds3231_t *dev,uint8_t date)
{
	dev->data.date.tens = date / 10;
	dev->data.date.units = date % 10;
	ds3231_data_write(dev,ds3231_add_date,&dev->data.date,1);
}
void ds3231_set_month(ds3231_t *dev,uint8_t month)
{
	dev->data.month.tens = month / 10;
	dev->data.month.units = month % 10;
	ds3231_data_write(dev,ds3231_add_month_century,&dev->data.month,1);
}
void ds3231_set_year(ds3231_t *dev,uint8_t year)
{
	dev->data.year.tens = year / 10;
	dev->data.year.units = year % 10;
	ds3231_data_write(dev,ds3231_add_year,&dev->data.year,1);
}
