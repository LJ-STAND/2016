#ifndef LIGHTSENSORCONTROLLER_H
#define LIGHTSENSORCONTROLLER_H

#include <Arduino.h>
#include <LightSensor.h>
#include <LineLocation.h>
#include <Pins.h>
#include <Config.h>
#include <Bluetooth.h>

class LightSensorController {
public:
    LightSensorController();

    void debugValues();
    void updateLineLocation();
    void calibrate();

    LineLocation lineLocation;

private:
    LightSensor lsLeftOuter;
    LightSensor lsLeftInner;
    LightSensor lsFrontOuter;
    LightSensor lsFrontInner;
    LightSensor lsRightOuter;
    LightSensor lsRightInner;
    LightSensor lsBackLeft;
    LightSensor lsBackRight;
};

extern LightSensorController lightSensorController;

#endif
