#include <Arduino.h>

#include "Robot.h"
#include "Config.h"
#include "Utils.h"

Robot robot;

uint32_t lastLoop = 0;

void setup()
{
    // setupFastPWM();
    // Serial.begin(9600);
    robot.begin();
}

void loop()
{
    uint32_t now =
        micros();

    if(now - lastLoop >= LOOP_TIME_US)
    {
        lastLoop = now ; 

        robot.update();
    }
}