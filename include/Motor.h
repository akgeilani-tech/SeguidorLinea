#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

class Motor
{
public:

    Motor();

    void begin();

    void enable();

    void disable();

    void setSpeed(
        int left,
        int right
    );

    void brake();

private:

    void driveMotor(
        uint8_t pwm,
        uint8_t in1,
        uint8_t in2,
        int speed
    );
};

#endif