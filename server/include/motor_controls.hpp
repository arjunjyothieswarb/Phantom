#ifndef __MOTOR_CONTROLS_HPP__
#define __MOTOR_CONTROLS_HPP__

#include "motor_driver.hpp"

#define CMD_STOP 0
#define CMD_UP 1
#define CMD_DOWN 2
#define CMD_LEFT 3
#define CMD_RIGHT 4

class CarControl
{
    int cmd;
    MotorDriver driver;

public:
    CarControl();
    void setCMD(int);
};

#endif