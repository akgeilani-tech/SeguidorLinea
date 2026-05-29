#include "Robot.h"
#include "Config.h"

Robot::Robot()
{
}

void Robot::begin()
{
    delay(500);

    sensors.begin();

    sensors.calibrate();
    if(!sensors.calibrate())
    {
        while(true)
        {
            // ERROR
        }
    }

    motors.begin();
}

void Robot::update()
{
    uint16_t position =
        sensors.readLine();

    int error =
        LINE_CENTER - position; 
    if(abs(error) < 20)
    {
        error = 0;
    }
    
    // Serial.print("Position: ");
    // Serial.print(position);

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
    
    correction =
    constrain(
        correction,
        -200,
        200
    );
}