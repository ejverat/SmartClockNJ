/* 
 * File:   motor_t.h
 * Author: evera
 *
 * Created on June 21, 2021, 2:53 AM
 * Description:
 * Struct and functions to manage motors directions, this don't manage the speed
 */

#ifndef MOTOR_T_H
#define	MOTOR_T_H

#ifdef	__cplusplus
extern "C" {
#endif
/**
 * Enumeration used to define the direction of the motor.
 */
    typedef enum
    {
        off, direction1, direction2
    } motor_direction_t;
/**
 * Struct to stores peripheral related functions to control the motor direction.
 * Since each motor require two pins to control direction, we need two functions
 * by pin to control high or low values of each.
 */
    typedef struct
    {
	    motor_direction_t direction;
        void (*pin_dir1_high_fn) (void);
        void (*pin_dir1_low_fn) (void);
        void (*pin_dir2_high_fn) (void);
        void (*pin_dir2_low_fn) (void);
    } motor_t;
/**
 * Set the direction of motor
 * @param motor motor to change direction
 * @param direction desired direction
 */
    void set_motor_direction(motor_t * motor, motor_direction_t direction);


#ifdef	__cplusplus
}
#endif

#endif	/* MOTOR_T_H */

