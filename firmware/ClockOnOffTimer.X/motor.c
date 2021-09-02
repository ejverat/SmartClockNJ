#include "motor.h"

void set_motor_direction(motor_t * motor, motor_direction_t direction)
{
    switch(direction)
    {
        case direction1:
            motor->pin_dir1_high_fn();
            motor->pin_dir2_low_fn();
        break;
        
        case direction2:
            motor->pin_dir1_low_fn();
            motor->pin_dir2_high_fn();
        break;
        
        case off:
            motor->pin_dir1_low_fn();
            motor->pin_dir2_low_fn();
        break;
        
        default:
        break;
    }
    motor->direction = direction;
}
