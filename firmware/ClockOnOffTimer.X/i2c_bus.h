/* 
 * File:   i2c_bus.h
 * Author: evera
 *
 * Created on August 10, 2021, 2:01 AM
 */

#ifndef I2C_BUS_H
#define	I2C_BUS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

	typedef struct
	{
		bool (*start_fn)(uint8_t);
		bool (*stop_fn)(void);
		bool (*read_fn)(uint8_t*,size_t);
		bool (*write_fn)(uint8_t*,size_t);
	} i2c_bus_t;

	typedef struct
	{
		i2c_bus_t *bus;
		uint8_t device_address;
		bool write;
		uint8_t *payload;
		size_t payload_size;
	} i2c_bus_message_t;

	bool i2c_do_transaction(i2c_bus_message_t *message);
	//bool i2c_write_then_read(i2c_bus_message_t *msg_w, i2c_bus_message_t *msg_r);

#ifdef	__cplusplus
}
#endif

#endif	/* I2C_BUS_H */

