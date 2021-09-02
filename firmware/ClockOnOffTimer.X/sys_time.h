/* 
 * File:   sys_time.h
 * Author: evera
 *
 * Created on July 6, 2021, 7:04 PM
 */

#ifndef SYS_TIME_H
#define	SYS_TIME_H

#include <inttypes.h>

#ifdef	__cplusplus
extern "C" {
#endif
	void sys_time_reset();
	uint32_t sys_time_get_ms();
	uint16_t sys_time_get_us();
	void sys_time_handler();



#ifdef	__cplusplus
}
#endif

#endif	/* SYS_TIME_H */

