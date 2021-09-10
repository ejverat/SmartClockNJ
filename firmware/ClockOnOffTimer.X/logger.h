/* 
 * File:   logger.h
 * Author: evera
 *
 * Created on September 7, 2021, 4:12 AM
 */

#ifndef LOGGER_H
#define	LOGGER_H

#include <stdint.h>

#define MAX_LOG_ENTRIES 100

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct 
{
	uint32_t timestamp;
	char text[5];
} log_entry_t;

void logger_add(const char log[5]);


#ifdef	__cplusplus
}
#endif

#endif	/* LOGGER_H */

