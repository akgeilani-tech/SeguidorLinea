#include "Sensors.h"
#include "Config.h"

Sensors::Sensors()
{
}

void Sensors::begin()
{
    qtr.setTypeAnalog();
    pinMode(SENSOR_Enable, OUTPUT);
    digitalWrite(SENSOR_Enable, HIGH);
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

bool Sensors::calibrate()
{
    pinMode(
        SENSOR_STATUS,
        OUTPUT
    );

    // ------------------------------------------
    // LED OFF
    // ------------------------------------------

    digitalWrite(
        SENSOR_STATUS,
        LOW
    );

    // ------------------------------------------
    // CALIBRACION
    // ------------------------------------------

    for(uint16_t i = 0; i < 450; i++)
    {
        qtr.calibrate();

        // --------------------------------------
        // BLINK
        // --------------------------------------

        digitalWrite(
            SENSOR_STATUS,
            !digitalRead(SENSOR_STATUS));

        delayMicroseconds(2500);
    }

    // ------------------------------------------
    // VERIFICAR CALIBRACION
    // ------------------------------------------

    bool calibrationOk = true;

    for(uint8_t i = 0; i < 8; i++)
    {
        uint16_t range =
            qtr.calibrationOn.maximum[i] -
            qtr.calibrationOn.minimum[i];

        if(range < 400)
        {
            calibrationOk = false;
        }
    }

    // ------------------------------------------
    // RESULTADO
    // ------------------------------------------

    if(calibrationOk)
    {
        // LED fijo ON

        digitalWrite(
            SENSOR_STATUS,
            HIGH
        );
    }
    else
    {
        // ERROR

        for(uint8_t i = 0; i < 10; i++)
        {
            digitalWrite(
                SENSOR_STATUS,
                HIGH
            );

            delay(100);

            digitalWrite(
                SENSOR_STATUS,
                LOW
            );

            delay(100);
        }
    }

    return calibrationOk;

}

uint16_t Sensors::readLine()
{
    return qtr.readLineBlack(
        values
    );
}