/* 
 * File:   pir.h
 * Author: evera
 *
 * Created on June 25, 2021, 4:11 AM
 * Description:
 * Struct to store the functions related with a pir sensor
 */

#ifndef PIR_H
#define	PIR_H

#ifdef	__cplusplus
extern "C" {
#endif

    typedef struct
    {
        unsigned (*pin_status_fn) (void);
        void (*handler_fn) (void);
    }pir_t;


#ifdef	__cplusplus
}
#endif

#endif	/* PIR_H */

