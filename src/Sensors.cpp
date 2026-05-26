#include "Sensors.h"

Sensors::Sensors()
{
}

void Sensors::begin()
{
    qtr.setTypeAnalog();

    qtr.setSensorPins(
        (const uint8_t[])
        {
            A0,
            A1,
            A2,
            A3,
            A4,
            A5,
            A6,
            A7
        },
        8
    );
}

void Sensors::calibrate()
{
    for(uint16_t i = 0; i < 400; i++)
    {
        qtr.calibrate();

        delayMicroseconds(1500);
    }
}

uint16_t Sensors::readLine()
{
    return qtr.readLineBlack(
        values
    );
}