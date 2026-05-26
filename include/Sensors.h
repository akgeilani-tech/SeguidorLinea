#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>
#include <QTRSensors.h>

class Sensors
{
public:

    Sensors();

    void begin();

    void calibrate();

    uint16_t readLine();

private:

    QTRSensors qtr;

    uint16_t values[8];
};

#endif