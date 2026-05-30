#include "Robot.h"
#include "Config.h"

Robot::Robot()
{
}

void Robot::rotateMotors(int leftSpeed, int rightSpeed)
{
    motors.setSpeed(leftSpeed, rightSpeed);
}

void Robot::begin()
{
    delay(500);

    sensors.begin();

    motors.begin();
}

void Robot::autoCalibrate()
{
    // ======================================
    // AUTOCALIBRACIÓN AUTOMÁTICA
    // ======================================

    // Pasar función lambda como callback
    sensors.autoCalibrateRotation(
        [this](int left, int right)
        {
            this->rotateMotors(left, right);
        }
    );
}

void Robot::update()
{
    uint16_t position =
        sensors.readLine();

    int error =
        LINE_CENTER - position; 
    if(abs(error) < 50)
    {
        error = 0;
    }

    float correction =
        pid.compute(error);

    int dynamicSpeed =
        BASE_SPEED -
        (abs(error) * CURVE_FACTOR);

    dynamicSpeed =
        constrain(
            dynamicSpeed,
            60,
            MAX_SPEED
        );

    int leftSpeed =
        dynamicSpeed + correction;

    int rightSpeed =
        dynamicSpeed - correction;

    leftSpeed =
        constrain(
            leftSpeed,
            MIN_SPEED,
            MAX_SPEED
        );

    rightSpeed =
        constrain(
            rightSpeed,
            MIN_SPEED,
            MAX_SPEED
        );

    motors.setSpeed(
        leftSpeed,
        rightSpeed
    );
}
