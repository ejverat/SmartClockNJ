/* 
 * File:   smart_pir.h
 * Author: evera
 *
 * Created on July 21, 2021, 6:38 PM
 */

#ifndef SMART_PIR_H
#define	SMART_PIR_H

#include <stdint.h>
#include <stdbool.h>
#include "pir.h"

#ifdef	__cplusplus
extern "C" {
#endif

	typedef struct
	{
		pir_t pir;
		bool status;
		bool device_status;
		uint32_t last_update;
		bool status_changed;
		uint32_t inactive_time;
		void (*enable_device_fn)(void);
		void (*disable_device_fn)(void);
	} smart_pir_t;

	void set_pir_status(smart_pir_t *pir, bool status);
	void smart_pir_device_monitor(smart_pir_t *pir);




#ifdef	__cplusplus
}
#endif

#endif	/* SMART_PIR_H */

