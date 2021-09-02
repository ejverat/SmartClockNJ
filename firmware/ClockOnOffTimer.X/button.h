/* 
 * File:   button.h
 * Author: evera
 *
 * Created on July 16, 2021, 5:09 AM
 */

#ifndef BUTTON_H
#define	BUTTON_H

#ifdef	__cplusplus
extern "C" {
#endif

	typedef enum 
	{
		button_none,
		button_inc,
		button_dec,
		button_ok
	} button_t;

	button_t get_user_input();




#ifdef	__cplusplus
}
#endif

#endif	/* BUTTON_H */

