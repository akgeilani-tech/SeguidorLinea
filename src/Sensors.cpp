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
    // CALIBRACION MANUAL
    // ------------------------------------------

    for(uint16_t i = 0; i < 450; i++)
    {
        qtr.calibrate();

        // BLINK

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
        // ERROR - Parpadeo rápido

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

bool Sensors::autoCalibrateRotation(std::function<void(int, int)> rotationCallback)
{
    pinMode(SENSOR_STATUS, OUTPUT);
    digitalWrite(SENSOR_STATUS, LOW);

    // ------------------------------------------
    // AUTOCALIBRACIÓN CON ROTACIÓN
    // ------------------------------------------

    for(uint8_t iter = 0; iter < AUTOCALIB_ITERATIONS; iter++)
    {
        // ======================================
        // GIRAR DERECHA (Left +, Right -)
        // ======================================

        uint32_t startTime = millis();

        while(millis() - startTime < AUTOCALIB_ROTATION_TIME_MS)
        {
            qtr.calibrate();

            // Parpadeo durante calibración
            digitalWrite(
                SENSOR_STATUS,
                !digitalRead(SENSOR_STATUS)
            );

            // Llamar callback para rotar motores
            rotationCallback(
                AUTOCALIB_ROTATION_SPEED,
                -AUTOCALIB_ROTATION_SPEED
            );

            delayMicroseconds(2500);
        }

        delay(500);

        // ======================================
        // GIRAR IZQUIERDA (Left -, Right +)
        // ======================================

        startTime = millis();

        while(millis() - startTime < AUTOCALIB_ROTATION_TIME_MS)
        {
            qtr.calibrate();

            // Parpadeo durante calibración
            digitalWrite(
                SENSOR_STATUS,
                !digitalRead(SENSOR_STATUS)
            );

            // Llamar callback para rotar motores
            rotationCallback(
                -AUTOCALIB_ROTATION_SPEED,
                AUTOCALIB_ROTATION_SPEED
            );

            delayMicroseconds(2500);
        }

        delay(500);
    }

    // ------------------------------------------
    // DETENER MOTORES
    // ------------------------------------------

    rotationCallback(0, 0);

    delay(500);

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
        // ERROR - Parpadeo rápido

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
