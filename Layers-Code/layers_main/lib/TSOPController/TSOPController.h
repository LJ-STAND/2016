#ifndef TSOPCONTROLLER_H
#define TSOPCONTROLLER_H

#include <Arduino.h>
#include <Bluetooth.h>
#include <Config.h>
#include <Pins.h>
#include <Maths.h>

class TSOPController {
public:
    int currentTSOP;
    int currentStrength;

    TSOPController();

    int ballDirection();
    void update();
    bool holdingBall();

    int filteredValues[TSOP_NUM];
    int TSOPValues[TSOP_NUM];

private:
    int loopCount;

    int TSOPPins[TSOP_NUM] = {
        TSOP_1,
        TSOP_2,
        TSOP_3,
        TSOP_4,
        TSOP_5,
        TSOP_6,
        TSOP_7,
        TSOP_8,
        TSOP_9,
        TSOP_10,
        TSOP_11,
        TSOP_12
    };

    int n = 0;

    void updateValues();
    void bestTSOP();
    void unlock();
};

extern TSOPController tsopController;

#endif
