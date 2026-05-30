#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>
#include <QTRSensors.h>
#include <functional>

class Sensors
{
public:

    Sensors();

    void begin();

    bool calibrate();

    bool autoCalibrateRotation(std::function<void(int, int)> rotationCallback);

    uint16_t readLine();

private:

    QTRSensors qtr;

    uint16_t values[8];
};

#endif
