#include "LightSensorArray.h"

LightSensorArray::LightSensorArray() {
    lsLeftOuter = LightSensor(LS_LEFT_OUTER);
    lsLeftMiddle = LightSensor(LS_LEFT_MIDDLE);
    lsLeftInner = LightSensor(LS_LEFT_INNER);
    lsFrontOuter = LightSensor(LS_FRONT_OUTER);
    lsFrontMiddle = LightSensor(LS_FRONT_MIDDLE);
    lsFrontInner = LightSensor(LS_FRONT_INNER);
    lsRightOuter = LightSensor(LS_RIGHT_OUTER);
    lsRightMiddle = LightSensor(LS_RIGHT_MIDDLE);
    lsRightInner = LightSensor(LS_RIGHT_INNER);
}

void LightSensorArray::LightSensorArraySetup(){
    lsLeftOuter.lightSensorSetup();
    lsLeftMiddle.lightSensorSetup();
    lsLeftInner.lightSensorSetup();
    lsFrontOuter.lightSensorSetup();
    lsFrontMiddle.lightSensorSetup();
    lsFrontInner.lightSensorSetup();
    lsRightOuter.lightSensorSetup();
    lsRightMiddle.lightSensorSetup();
    lsRightInner.lightSensorSetup();
}

void LightSensorArray::updateLineLocation() {
    bool lsLeftOuterOnWhite = lsLeftOuter.isOnWhite();
    bool lsLeftMiddleOnWhite = lsLeftMiddle.isOnWhite();
    bool lsLeftInnerOnWhite = lsLeftInner.isOnWhite();
    bool lsRightOuterOnWhite = lsRightOuter.isOnWhite();
    bool lsRightMiddleOnWhite = lsRightMiddle.isOnWhite();
    bool lsRightInnerOnWhite = lsRightInner.isOnWhite();
    bool lsFrontOuterOnWhite = lsFrontOuter.isOnWhite();
    bool lsFrontMiddleOnWhite = lsFrontMiddle.isOnWhite();
    bool lsFrontInnerOnWhite = lsFrontOuter.isOnWhite();

    lsFront = (int)lsFrontOuterOnWhite + 2 * (int)lsFrontMiddleOnWhite + 3 * (int)lsFrontInnerOnWhite;

    lsLeft = (int)lsLeftOuterOnWhite + 2 * (int)lsLeftMiddleOnWhite + 3 * (int)lsLeftInnerOnWhite;

    lsRight = (int)lsRightOuterOnWhite + 2 * (int)lsRightMiddleOnWhite + 3 * (int)lsRightInnerOnWhite;

    if ((lsFront + lsLeft + lsRight) == 0){
        lineLocation = LineLocation::field;
        lineMag = 0;
    } else {
        if (lsFront != 0){
            if (lsLeft == 0 && lsRight == 0){
                lineLocation = LineLocation::front;
                lineMag = lsFront;
            }
            else if (lsLeft > lsRight) {
                lineLocation = LineLocation::cornerFrontLeft;
                lineMag = max(lsFront, lsLeft);
            }
            else if (lsRight > lsLeft) {
                lineLocation = LineLocation::cornerFrontRight;
                lineMag = max(lsFront, lsRight);
            }
            else {
                lineLocation = LineLocation::back;
                lineMag = lsLeft;
            }
        } else if (lsLeft != 0 && lsRight != 0) {
            if (lsLeft == lsRight){
                lineLocation = LineLocation::back;
                lineMag = lsLeft;
            } else if (lsLeft > lsRight){
                lineLocation = LineLocation::cornerBackLeft;
                lineMag = lsLeft;
            } else {
                lineLocation = LineLocation::cornerBackRight;
                lineMag = lsRight;
            }
        } else if (lsLeft != 0) {
            lineLocation = LineLocation::left;
            lineMag = lsLeft;
        } else {
            lineLocation = LineLocation::right;
            lineMag = lsRight;
        }
    }
}
