#include "motor_controls.hpp"

void CarControl::setCMD(int cmd)
{
    switch (cmd)
    {
    case CMD_UP:
        driver.set_motor_direction(MOTOR_LEFT, DIRECTION_ANTICLOCK_WISE);
        driver.set_motor_direction(MOTOR_RIGHT, DIRECTION_CLOCK_WISE);
        break;
    case CMD_DOWN:
        driver.set_motor_direction(MOTOR_LEFT, DIRECTION_CLOCK_WISE);
        driver.set_motor_direction(MOTOR_RIGHT, DIRECTION_ANTICLOCK_WISE);
        break;
    case CMD_LEFT:
        driver.set_motor_direction(MOTOR_LEFT, DIRECTION_CLOCK_WISE);
        driver.set_motor_direction(MOTOR_RIGHT, DIRECTION_CLOCK_WISE);
        break;
    case CMD_RIGHT:
        driver.set_motor_direction(MOTOR_LEFT, DIRECTION_ANTICLOCK_WISE);
        driver.set_motor_direction(MOTOR_RIGHT, DIRECTION_ANTICLOCK_WISE);
        break;

    default:
        driver.set_motor_direction(MOTOR_LEFT, DIRECTION_STOP);
        driver.set_motor_direction(MOTOR_RIGHT, DIRECTION_STOP);
        break;
    }
    return;
}