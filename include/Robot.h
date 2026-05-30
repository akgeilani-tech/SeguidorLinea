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

    void autoCalibrate();

private:

    Motor motors;

    PID pid;

    Sensors sensors;

    void rotateMotors(int leftSpeed, int rightSpeed);
};

#endif
