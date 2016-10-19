#ifndef LIGHTSENSOR_H
#define LIGHTSENSOR_H

#include <Arduino.h>
#include <Config.h>
#include <Bluetooth.h>

class LightSensor {
public:
    LightSensor() {}
    LightSensor(int in);
    void calibrate();

    int read();
    bool isOnWhite();

private:
    int inPin;
    int thresholdValue;
};

#endif
