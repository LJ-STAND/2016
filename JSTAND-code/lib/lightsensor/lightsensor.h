#ifndef LIGHTSENSOR_H
#define LIGHTSENSOR_H

#include <Arduino.h>
#include <defines.h>

class LightSensor {
public:
    LightSensor() {}
    LightSensor(int in, int threshold = DEFAULT_LS_THRESHOLD);

    void lightSensorSetup();

    void setThreshold(int thresh);

    void read();
    bool isOnWhite();

    int readValue;

private:
    int inPin;
    int thresholdValue;
};

#endif
