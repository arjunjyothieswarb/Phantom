#include "motor_driver.hpp"

MotorDriver::MotorDriver()
{
    // Initializing GPIOs
    wiringPiSetupGpio();

    left_motor_enable = false;
    right_motor_enable = false;

    // Setting gpios to output
    pinMode(GPIO_IN_LEFT_1, OUTPUT);
    pinMode(GPIO_IN_LEFT_2, OUTPUT);
    pinMode(GPIO_IN_RIGHT_1, OUTPUT);
    pinMode(GPIO_IN_RIGHT_2, OUTPUT);
}

void MotorDriver::set_motor_state(int motor, int state)
{
    if (motor == MOTOR_LEFT)
        left_motor_enable = state;
    else if (motor == MOTOR_RIGHT)
        right_motor_enable = state;
    return;
}

int MotorDriver::get_motor_state(int motor)
{
    if (motor == MOTOR_LEFT)
        return left_motor_enable;
    else if (motor == MOTOR_RIGHT)
        return right_motor_enable;
    return -1;
}

void MotorDriver::set_motor_direction(int motor, int direction)
{
    in1 = 0;
    in2 = 0;

    switch (direction)
    {
    case DIRECTION_CLOCK_WISE:
        in1 = 0;
        in2 = 1;
        break;
    case DIRECTION_ANTICLOCK_WISE:
        in1 = 1;
        in2 = 0;
        break;
    default:
        in1 = 0;
        in2 = 0;
        break;
    }

    switch (motor)
    {
    case MOTOR_LEFT:
        /* code */
        digitalWrite(GPIO_IN_LEFT_1, in1);
        digitalWrite(GPIO_IN_LEFT_2, in2);
        break;
    case MOTOR_RIGHT:
        /* code */
        digitalWrite(GPIO_IN_RIGHT_1, in1);
        digitalWrite(GPIO_IN_RIGHT_2, in2);
        break;
    }

    return;
}
