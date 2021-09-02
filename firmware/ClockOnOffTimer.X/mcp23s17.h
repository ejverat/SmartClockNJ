/* 
 * File:   MCP23S17.h
 * Author: evera
 *
 * Created on July 5, 2021, 11:35 PM
 */

#ifndef MCP23S17_H
#define	MCP23S17_H

#include <inttypes.h>
#include <stdio.h>
#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif
#define IODIRA 		0x0000
#define IODIRB 		0x1001
#define IPOLA 		0x0102
#define IPOLB 		0x1103
#define GPINTENA 	0x0204
#define GPINTENB 	0x1205
#define DEFVALA 	0x0306
#define DEFVALB 	0x1307
#define INTCONA 	0x0408
#define INTCONB 	0x1409
#define IOCONA 		0x050A
#define IOCONB 		0x150B
#define GPPUA 		0x060C
#define GPPUB 		0x160D
#define INTFA 		0x070E
#define INTFB 		0x170F
#define INTCAPA 	0x0810
#define INTCAPB 	0x1811
#define GPIOA 		0x0912
#define GPIOB 		0x1913
#define OLATA 		0x0A14
#define OLATB 		0x1A15

#define CONTROL_BYTE 	0x04
#define READ_BIT 	0x01
#define WRITE_BIT 	0x00

	typedef struct
	{
		void (*enable)(void);
		void (*disable)(void);
		void (*reset_low_fn)(void);
		void (*reset_high_fn)(void);
		void (*write_fn)(void*, size_t);
		uint8_t (*read_fn)(void);
		uint8_t address;
		uint8_t porta_value;
		uint8_t portb_value;
	} mcp23s17_t;

	typedef enum {mcp23s17_porta,mcp23s17_portb} mcp23s17_port_t;


	static void mcp23s17_write(mcp23s17_t *dev, uint8_t reg, uint8_t byte);

	static uint8_t mcp23s17_read(mcp23s17_t *dev, uint8_t reg);

	void mcp23s17_port_dir(mcp23s17_t *dev, mcp23s17_port_t port, uint8_t config);
	void mcp23s17_port_polarity(mcp23s17_t *dev, mcp23s17_port_t port, uint8_t config);
	void mcp23s17_port_pullups(mcp23s17_t *dev, mcp23s17_port_t port, uint8_t config);
	uint8_t mcp23s17_read_port(mcp23s17_t *dev, mcp23s17_port_t port);
	void mcp23s17_write_port(mcp23s17_t *dev, mcp23s17_port_t port);
	void mcp23s17_init(mcp23s17_t *dev);



#ifdef	__cplusplus
}
#endif

#endif	/* MCP23S17_H */

