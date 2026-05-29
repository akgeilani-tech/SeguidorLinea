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

bool Sensors::calibrate()
{
    pinMode(
        LED_BUILTIN,
        OUTPUT
    );

    // ------------------------------------------
    // LED OFF
    // ------------------------------------------

    digitalWrite(
        LED_BUILTIN,
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
            LED_BUILTIN,
            !digitalRead(LED_BUILTIN)
        );

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
            LED_BUILTIN,
            HIGH
        );
    }
    else
    {
        // ERROR

        for(uint8_t i = 0; i < 10; i++)
        {
            digitalWrite(
                LED_BUILTIN,
                HIGH
            );

            delay(100);

            digitalWrite(
                LED_BUILTIN,
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