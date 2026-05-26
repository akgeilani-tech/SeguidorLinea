#ifndef ROBOT_H
#define ROBOT_H

#include "Motor.h"
#include "PID.h"
#include "Sensors.h"

class Robot
{
public:

    Robot();

    void begin();

    void update();

private:

    Motor motors;

    PID pid;

    Sensors sensors;
};

#endif