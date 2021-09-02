#include "ds1307.h"
#include "i2c_bus.h"
#include <string.h>
#include <stdbool.h>

void ds1307_read_all(ds1307_t *dev)
{
	i2c_bus_message_t msg;

	/* set memory map address pointer */
	uint8_t mem_address = 0x00;
	msg.bus = dev->bus;
	msg.device_address = DS1307_I2C_ADD;
	msg.write = true;
	msg.payload_size = 1;
	msg.payload = &mem_address;

	i2c_do_transaction(&msg);

	/* read memory */
	msg.write = false;
	msg.payload = dev->data.bytes;
	msg.payload_size = DS1307_MEM_SIZE;

	i2c_do_transaction(&msg);
}

uint8_t ds1307_get_seconds(ds1307_t *dev)
{
	i2c_bus_message_t msg;

	/* set memory map address pointer */
	uint8_t mem_address = ds1307_addrs_seconds;
	msg.bus = dev->bus;
	msg.device_address = DS1307_I2C_ADD;
	msg.write = true;
	msg.payload_size = 1;
	msg.payload = &mem_address;

	i2c_do_transaction(&msg);

	/* read memory */
	msg.write = false;
	msg.payload = &dev->data.seconds;
	msg.payload_size = 1;

	i2c_do_transaction(&msg);

	return dev->data.seconds.tens*10+dev->data.seconds.units;
}

uint8_t ds1307_get_minutes(ds1307_t *dev)
{
	i2c_bus_message_t msg;

	/* set memory map address pointer */
	uint8_t mem_address = ds1307_addrs_minutes;
	msg.bus = dev->bus;
	msg.device_address = DS1307_I2C_ADD;
	msg.write = true;
	msg.payload_size = 1;
	msg.payload = &mem_address;

	i2c_do_transaction(&msg);

	/* read memory */
	msg.write = false;
	msg.payload = &dev->data.minutes;
	msg.payload_size = 1;

	i2c_do_transaction(&msg);

	return dev->data.minutes.tens*10+dev->data.minutes.units;
}

uint8_t ds1307_get_hours(ds1307_t *dev)
{
	i2c_bus_message_t msg;

	/* set memory map address pointer */
	uint8_t mem_address = ds1307_addrs_hours;
	msg.bus = dev->bus;
	msg.device_address = DS1307_I2C_ADD;
	msg.write = true;
	msg.payload_size = 1;
	msg.payload = &mem_address;

	i2c_do_transaction(&msg);

	/* read memory */
	msg.write = false;
	msg.payload = &dev->data.hours;
	msg.payload_size = 1;

	i2c_do_transaction(&msg);
	
	/* validate hour format */
	if (dev->data.hours.f12_24 == 0)
	{
		return dev->data.hours.twenties*20 + dev->data.hours.tens*10 + dev->data.hours.units;
	}

	return dev->data.hours.tens*10+dev->data.hours.units;
}

uint8_t ds1307_get_day(ds1307_t *dev)
{
	i2c_bus_message_t msg;

	/* set memory map address pointer */
	uint8_t mem_address = ds1307_addrs_day;
	msg.bus = dev->bus;
	msg.device_address = DS1307_I2C_ADD;
	msg.write = true;
	msg.payload_size = 1;
	msg.payload = &mem_address;

	i2c_do_transaction(&msg);

	/* read memory */
	msg.write = false;
	msg.payload = &dev->data.day;
	msg.payload_size = 1;

	i2c_do_transaction(&msg);
	
	return dev->data.day.day;
}

uint8_t ds1307_get_date(ds1307_t *dev)
{
	i2c_bus_message_t msg;

	/* set memory map address pointer */
	uint8_t mem_address = ds1307_addrs_date;
	msg.bus = dev->bus;
	msg.device_address = DS1307_I2C_ADD;
	msg.write = true;
	msg.payload_size = 1;
	msg.payload = &mem_address;

	i2c_do_transaction(&msg);

	/* read memory */
	msg.write = false;
	msg.payload = &dev->data.date;
	msg.payload_size = 1;

	i2c_do_transaction(&msg);
	
	return dev->data.date.tens*10 + dev->data.date.units;
}

uint8_t ds1307_get_month(ds1307_t *dev)
{
	i2c_bus_message_t msg;

	/* set memory map address pointer */
	uint8_t mem_address = ds1307_addrs_month;
	msg.bus = dev->bus;
	msg.device_address = DS1307_I2C_ADD;
	msg.write = true;
	msg.payload_size = 1;
	msg.payload = &mem_address;

	i2c_do_transaction(&msg);

	/* read memory */
	msg.write = false;
	msg.payload = &dev->data.month;
	msg.payload_size = 1;

	i2c_do_transaction(&msg);
	
	return dev->data.month.tens*10 + dev->data.month.units;
}

uint8_t ds1307_get_year(ds1307_t *dev)
{
	i2c_bus_message_t msg;

	/* set memory map address pointer */
	uint8_t mem_address = ds1307_addrs_year;
	msg.bus = dev->bus;
	msg.device_address = DS1307_I2C_ADD;
	msg.write = true;
	msg.payload_size = 1;
	msg.payload = &mem_address;

	i2c_do_transaction(&msg);

	/* read memory */
	msg.write = false;
	msg.payload = &dev->data.year;
	msg.payload_size = 1;

	i2c_do_transaction(&msg);
	
	return dev->data.year.tens*10 + dev->data.year.units;
}

void ds1307_set_seconds(ds1307_t *dev,uint8_t seconds)
{
	dev->data.seconds.tens = seconds/10;
	dev->data.seconds.units = seconds % 10;
	dev->data.seconds.ch = 0;

	i2c_bus_message_t msg;

	/* set memory map address pointer */
	uint8_t payload[2];
	payload[0] = ds1307_addrs_seconds;
	memcpy(&payload[1],&dev->data.seconds,1);
	msg.bus = dev->bus;
	msg.device_address = DS1307_I2C_ADD;
	msg.write = true;
	msg.payload_size = 2;
	msg.payload = payload;

	i2c_do_transaction(&msg);

}

void ds1307_set_minutes(ds1307_t *dev,uint8_t minutes)
{
	dev->data.minutes.tens = minutes/10;
	dev->data.minutes.units = minutes % 10;

	i2c_bus_message_t msg;

	/* set memory map address pointer */
	uint8_t payload[2];
	payload[0] = ds1307_addrs_minutes;
	memcpy(&payload[1],&dev->data.minutes,1);
	msg.bus = dev->bus;
	msg.device_address = DS1307_I2C_ADD;
	msg.write = true;
	msg.payload_size = 2;
	msg.payload = payload;

	i2c_do_transaction(&msg);

}

void ds1307_set_hours_f24(ds1307_t *dev,uint8_t hours)
{
	dev->data.hours.twenties = 0;
	dev->data.hours.tens = 0;
	if (hours > 20)
	{
		dev->data.hours.twenties = 1;
	}
	else
	{
		dev->data.hours.tens = hours/10;
	}

	dev->data.hours.units = hours%10;
	dev->data.hours.f12_24 = 0;

	i2c_bus_message_t msg;

	/* set memory map address pointer */
	uint8_t payload[2];
	payload[0] = ds1307_addrs_hours;
	memcpy(&payload[1],&dev->data.hours,1);
	msg.bus = dev->bus;
	msg.device_address = DS1307_I2C_ADD;
	msg.write = true;
	msg.payload_size = 2;
	msg.payload = payload;

	i2c_do_transaction(&msg);

}

void ds1307_set_hours_f12(ds1307_t *dev,uint8_t hours, bool pm)
{
	if (pm)
	{
		dev->data.hours.am_pm = 1;
	}
	else
	{
		dev->data.hours.am_pm = 0;
	}
	dev->data.hours.tens = hours/10;
	dev->data.hours.units = hours%10;
	dev->data.hours.f12_24 = 1;

	i2c_bus_message_t msg;

	/* set memory map address pointer */
	uint8_t payload[2];
	payload[0] = ds1307_addrs_hours;
	memcpy(&payload[1],&dev->data.hours,1);
	msg.bus = dev->bus;
	msg.device_address = DS1307_I2C_ADD;
	msg.write = true;
	msg.payload_size = 2;
	msg.payload = payload;

	i2c_do_transaction(&msg);

}

void ds1307_set_day(ds1307_t *dev,uint8_t day)
{
	dev->data.day.day = day;
	i2c_bus_message_t msg;

	/* set memory map address pointer */
	uint8_t payload[2];
	payload[0] = ds1307_addrs_day;
	memcpy(&payload[1],&dev->data.day,1);
	msg.bus = dev->bus;
	msg.device_address = DS1307_I2C_ADD;
	msg.write = true;
	msg.payload_size = 2;
	msg.payload = payload;

	i2c_do_transaction(&msg);

}

void ds1307_set_date(ds1307_t *dev,uint8_t date)
{
	dev->data.date.tens = date/10;
	dev->data.date.units = date % 10;

	i2c_bus_message_t msg;

	/* set memory map address pointer */
	uint8_t payload[2];
	payload[0] = ds1307_addrs_date;
	memcpy(&payload[1],&dev->data.date,1);
	msg.bus = dev->bus;
	msg.device_address = DS1307_I2C_ADD;
	msg.write = true;
	msg.payload_size = 2;
	msg.payload = payload;

	i2c_do_transaction(&msg);

}

void ds1307_set_month(ds1307_t *dev,uint8_t month)
{
	dev->data.month.tens = month/10;
	dev->data.month.units = month % 10;

	i2c_bus_message_t msg;

	/* set memory map address pointer */
	uint8_t payload[2];
	payload[0] = ds1307_addrs_month;
	memcpy(&payload[1],&dev->data.month,1);
	msg.bus = dev->bus;
	msg.device_address = DS1307_I2C_ADD;
	msg.write = true;
	msg.payload_size = 2;
	msg.payload = payload;

	i2c_do_transaction(&msg);

}

void ds1307_set_year(ds1307_t *dev,uint8_t year)
{
	dev->data.year.tens = year/10;
	dev->data.year.units = year % 10;

	i2c_bus_message_t msg;

	/* set memory map address pointer */
	uint8_t payload[2];
	payload[0] = ds1307_addrs_year;
	memcpy(&payload[1],&dev->data.year,1);
	msg.bus = dev->bus;
	msg.device_address = DS1307_I2C_ADD;
	msg.write = true;
	msg.payload_size = 2;
	msg.payload = payload;

	i2c_do_transaction(&msg);

}
