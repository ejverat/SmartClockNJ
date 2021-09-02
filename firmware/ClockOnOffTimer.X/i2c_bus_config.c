#include "i2c_bus_config.h"
#include "mcc_generated_files/i2c2_master.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

static bool i2c2_start(uint8_t dev_address);
static bool i2c2_stop();
static bool i2c2_read(uint8_t *buff, size_t size);
static bool i2c2_write(uint8_t *buff, size_t size);

void i2c_bus_config(i2c_bus_t *bus)
{
	bus->start_fn = i2c2_start;
	bus->stop_fn = i2c2_stop;
	bus->read_fn = i2c2_read;
	bus->write_fn = i2c2_write;
}

static bool i2c2_start(uint8_t address)
{

	i2c2_error_t status;
	do
	{
		status = I2C2_Open(address);
	}while(I2C2_BUSY == status);

	return status == I2C2_NOERR;
}

static bool i2c2_stop()
{
	i2c2_error_t status;
	do
	{
		status = I2C2_Close();
	}while(I2C2_BUSY == status);

	return status == I2C2_NOERR;
}

static bool i2c2_read(uint8_t* buff, size_t size)
{
	I2C2_SetBuffer(buff, size);
	i2c2_error_t status;
	do
	{
		status = I2C2_MasterOperation(true);
	}while(I2C2_BUSY == status);

	return status == I2C2_NOERR;
}

static bool i2c2_write(uint8_t* buff, size_t size)
{
	I2C2_SetBuffer(buff, size);
	i2c2_error_t status;
	do
	{
		status = I2C2_MasterOperation(false);
	}while(I2C2_BUSY == status);

	return status == I2C2_NOERR;
}
