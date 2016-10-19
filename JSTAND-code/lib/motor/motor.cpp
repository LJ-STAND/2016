/* Library of simple motor functions.
 */
#include "motor.h"

#include <jstandcommon.h>

Motor::Motor(int standby, int dirOne, int dirTwo, int pwm, int angle, bool reversed) {
    standbyPin = standby;
    dirOnePin = dirOne;
    dirTwoPin = dirTwo;
    pwmPin = pwm;
    dirReversed = reversed;
    dirAngle = angle;
}

void Motor::move(double speed, int max) {
    int newDirOne, newDirTwo, signedDir;
    double newPwm;
    if ((int)speed == 0) {
        newDirOne = 0;
        newDirTwo = 0;
        newPwm = 255;
    } else {
        signedDir = (sign(speed) * (((int)dirReversed << 1) - 1));
        newDirOne = (signedDir + 1) >> 1;
        newDirTwo = newDirOne ^ 1;
        newPwm = constrain((int)(doubleAbs(speed) * 255 / max), 0, 255);
    }
    digitalWrite(standbyPin, 1);
    digitalWrite(dirOnePin, newDirOne);
    digitalWrite(dirTwoPin, newDirTwo);
    analogWrite(pwmPin, newPwm);
}

void Motor::move(int speed, int max){
    move((double)speed, max);
}

void Motor::motorSetup() {
    pinMode(standbyPin, OUTPUT);
    pinMode(dirOnePin, OUTPUT);
    pinMode(dirTwoPin, OUTPUT);
    pinMode(pwmPin, OUTPUT);
}

int Motor::getAngle() {
    return dirAngle;
}
