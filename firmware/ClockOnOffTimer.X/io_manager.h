/* 
 * File:   io_manager.h
 * Author: evera
 *
 * Created on July 5, 2021, 2:59 AM
 */

#ifndef IO_MANAGER_H
#define	IO_MANAGER_H

#include <inttypes.h>
#include "mcp23s17.h"

#ifdef	__cplusplus
extern "C" {
#endif
	void set_motor1_O1_high();
	void set_motor1_O1_low();
	void set_motor1_O2_high();
	void set_motor1_O2_low();

	unsigned get_button0_status();
	unsigned get_button1_status();
	unsigned get_button2_status();
	unsigned get_PIR1();
	void spi_cs_low();
	void spi_cs_high();
	void spi_write_bytes(uint8_t *bytes, unsigned int nbytes);


#ifdef	__cplusplus
}
#endif

#endif	/* IO_MANAGER_H */

