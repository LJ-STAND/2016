#include "LightSensorController.h"

LightSensorController::LightSensorController() {
    lsLeftOuter = LightSensor(LS_LEFT_OUTER);
    lsLeftInner = LightSensor(LS_LEFT_INNER);
    lsFrontOuter = LightSensor(LS_FRONT_OUTER);
    lsFrontInner = LightSensor(LS_FRONT_INNER);
    lsRightOuter = LightSensor(LS_RIGHT_OUTER);
    lsRightInner = LightSensor(LS_RIGHT_INNER);
    lsBackLeft = LightSensor(LS_BACK_LEFT);
    lsBackRight = LightSensor(LS_BACK_RIGHT);
}

void LightSensorController::calibrate() {
    lsLeftOuter.calibrate();
    lsLeftInner.calibrate();
    lsFrontOuter.calibrate();
    lsFrontInner.calibrate();
    lsRightOuter.calibrate();
    lsRightInner.calibrate();
    lsBackLeft.calibrate();
    lsBackRight.calibrate();
}

void LightSensorController::debugValues() {
    Bluetooth::send(String(lsLeftOuter.read()) + ", " + String(lsLeftInner.read()) + ", " + String(lsFrontOuter.read()) + ", " + String(lsFrontInner.read()) + ", " + String(lsRightOuter.read()) + ", " + String(lsRightInner.read()) + ", " + String(lsBackLeft.read()) + ", " + String(lsBackRight.read()));
}

void LightSensorController::updateLineLocation() {
    #if LIGHT_SENSOR_DEBUG
        debugValues();
    #endif

      #if LIGHT_SENSORS_ENABLED
        bool lsLeftOuterOnWhite = false;
        bool lsLeftInnerOnWhite = lsLeftInner.isOnWhite();
        bool lsRightOuterOnWhite = false;
        bool lsRightInnerOnWhite = lsRightInner.isOnWhite();
        bool lsFrontOuterOnWhite = false;
        bool lsFrontInnerOnWhite = lsFrontInner.isOnWhite();
        bool lsBackLeftOnWhite = lsBackLeft.isOnWhite();
        bool lsBackRightOnWhite = lsBackRight.isOnWhite();

        if (lsLeftOuterOnWhite || lsLeftInnerOnWhite) {
            if (lsFrontOuterOnWhite || lsFrontInnerOnWhite) {
                lineLocation = LineLocation::cornerFrontLeft;
            } else if (lsBackLeftOnWhite || lsBackRightOnWhite) {
                lineLocation = LineLocation::cornerBackLeft;
            } else if (lsRightInnerOnWhite || lsRightOuterOnWhite) {
                lineLocation = LineLocation::frontMiddle;
            } else {
                lineLocation = LineLocation::left;
            }
        } else if (lsRightOuterOnWhite || lsRightInnerOnWhite) {
            if (lsFrontOuterOnWhite || lsFrontInnerOnWhite) {
                lineLocation = LineLocation::cornerFrontRight;
            } else if (lsBackLeftOnWhite || lsBackRightOnWhite) {
                lineLocation = LineLocation::cornerBackRight;
            } else {
                lineLocation = LineLocation::right;
            }
        } else if (lsFrontOuterOnWhite || lsFrontInnerOnWhite) {
            lineLocation = LineLocation::front;
        } else if (lsBackLeftOnWhite || lsBackRightOnWhite) {
            lineLocation = LineLocation::back;
        } else {
            lineLocation = LineLocation::field;
        }
    #else
        lineLocation = LineLocation::field;
    #endif
}
