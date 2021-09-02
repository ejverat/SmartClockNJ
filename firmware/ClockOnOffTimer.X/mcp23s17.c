#include "mcp23s17.h"
#include "mcc_generated_files/spi1.h"  

static void mcp23s17_write(mcp23s17_t *dev, uint8_t reg, uint8_t byte)
{
	uint8_t bytes[3];
	bytes[0] = (CONTROL_BYTE << 4) | (dev->address << 1) | WRITE_BIT;
	bytes[1] = reg;
	bytes[2] = byte;
	dev->enable();
    dev->write_fn(bytes,3);
	dev->disable();
}

static uint8_t mcp23s17_read(mcp23s17_t *dev, uint8_t reg)
{
	uint8_t bytes[2];
	bytes[0] = (CONTROL_BYTE << 4) | (dev->address << 1) | READ_BIT;
	bytes[1] = reg;
	dev->enable();
	dev->write_fn(bytes,2);
	uint8_t byte = dev->read_fn();
	dev->disable();
	return byte;
}

void mcp23s17_port_dir(mcp23s17_t *dev, mcp23s17_port_t port, uint8_t config)
{
	uint8_t reg = port == mcp23s17_porta? (IODIRA&0xff) : (IODIRB&0xff);
	mcp23s17_write(dev, reg, config);
}

void mcp23s17_port_polarity(mcp23s17_t *dev, mcp23s17_port_t port, uint8_t config)
{
	uint8_t reg = port == mcp23s17_porta? (IPOLA&0xff) : (IPOLB&0xff);
	mcp23s17_write(dev, reg, config);
}

void mcp23s17_port_pullups(mcp23s17_t *dev, mcp23s17_port_t port, uint8_t config)
{
	uint8_t reg = port == mcp23s17_porta? (GPPUA&0xff) : (GPPUB&0xff);
	mcp23s17_write(dev, reg, config);
}

uint8_t mcp23s17_read_port(mcp23s17_t *dev, mcp23s17_port_t port)
{
	uint8_t reg = port == mcp23s17_porta? (GPIOA&0xff) : (GPIOB&0xff);
	return mcp23s17_read(dev, reg);
}

void mcp23s17_write_port(mcp23s17_t *dev, mcp23s17_port_t port)
{
	if(port == mcp23s17_porta)
	{
		mcp23s17_write(dev,OLATA&0xff,dev->porta_value);
	}
	else
	{
		mcp23s17_write(dev,OLATB&0xff,dev->portb_value);
	}
}

void mcp23s17_init(mcp23s17_t *dev)
{
	mcp23s17_write(dev,GPPUA&0xff,0x0f);
	mcp23s17_write(dev,IOCONB&0xff,0x40);
	mcp23s17_write(dev,IODIRA&0xff,0xff);
	mcp23s17_write(dev,IODIRB&0xff,0xff);
}
