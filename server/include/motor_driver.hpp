#ifndef __MOTOR_DRIVER_HPP__
#define __MOTOR_DRIVER_HPP__

#include <wiringPi.h>

#define GPIO_IN_LEFT_1 17
#define GPIO_IN_LEFT_2 27

#define GPIO_IN_RIGHT_1 22
#define GPIO_IN_RIGHT_2 23

#define MOTOR_LEFT 0
#define MOTOR_RIGHT 1

#define DIRECTION_STOP 0
#define DIRECTION_CLOCK_WISE 1
#define DIRECTION_ANTICLOCK_WISE 2

class MotorDriver
{
    bool right_motor_enable;
    bool left_motor_enable;
    int in1, in2;

public:
    MotorDriver();
    void set_motor_direction(int motor, int direction);
    int get_motor_state(int motor);
    void set_motor_state(int motor, int state);
};

#endif