#include "PID.h"
#include "Config.h"

PID::PID()
{
    integral = 0;
    derivative = 0;
    lastError = 0;
}

float PID::compute(
    int error
)
{
    integral += error;

    derivative = error - lastError;

    lastError = error;

    return
        (KP * error) +
        (KI * integral) +
        (KD * derivative);
}

void PID::reset()
{
    integral = 0;
    derivative = 0;
    lastError = 0;
}