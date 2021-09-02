/* 
 * File:   display_pos.h
 * Author: evera
 *
 * Created on August 18, 2021, 3:06 AM
 */

#ifndef DISPLAY_POS_H
#define	DISPLAY_POS_H

#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif

	typedef struct 
	{
		uint8_t col;
		uint8_t row;
	} display_pos_t;



#ifdef	__cplusplus
}
#endif

#endif	/* DISPLAY_POS_H */

