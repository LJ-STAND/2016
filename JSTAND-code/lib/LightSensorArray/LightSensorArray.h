#ifndef LIGHTSENSORARRAY_H
#define LIGHTSENSORARRAY_H

#include <Arduino.h>
#include <lightsensor.h>
#include <linelocation.h>

class LightSensorArray {
public:
    LightSensorArray();

    void debugValues();
    void updateLineLocation();
    void LightSensorArraySetup();

    LineLocation lineLocation;

    int lineMag = 0;

// private:
    LightSensor lsLeftOuter;
    LightSensor lsLeftMiddle;
    LightSensor lsLeftInner;
    LightSensor lsFrontOuter;
    LightSensor lsFrontMiddle;
    LightSensor lsFrontInner;
    LightSensor lsRightOuter;
    LightSensor lsRightMiddle;
    LightSensor lsRightInner;

    int lsFront = 0;
    int lsLeft = 0;
    int lsRight = 0;
};

// extern LightSensorArray lights;

#endif
