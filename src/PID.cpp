#include "PID.h"
#include "Config.h"

PID::PID()
{
    integral = 0;
    derivative = 0;
    derivativeFiltered = 0;
    lastError = 0;
}

float PID::compute(
    int error
)
{
    integral += error;
    integral =
        constrain(
            integral,
            -1000,
            1000
        );

    derivative = error - lastError;
    
    derivativeFiltered =
        (derivativeFiltered * 0.7f) +
        (derivative * 0.3f);

    lastError = error;

    return
        (KP * error) +
        (KI * integral) +
        (KD * derivativeFiltered);
}

void PID::reset()
{
    integral = 0;
    derivative = 0;
    derivativeFiltered = 0;
    lastError = 0;
}