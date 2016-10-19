/* Library of simple motor functions.
 */

#ifndef LIB_MOTOR_MOTOR_H_
#define LIB_MOTOR_MOTOR_H_

#include "arduino.h"

//#include <jstandcommon.h>

class Motor{
 public:
    Motor(int standby, int dirOne, int dirTwo, int pwm, int angle, bool reversed = false);
    Motor(){}
    void move(double speed, int max = 100);
    void move(int speed, int max = 100);
    void motorSetup();
    int getAngle();

 private:
    int standbyPin, dirOnePin, dirTwoPin, pwmPin, dirAngle;
    bool dirReversed;
};

#endif  // LIB_MOTOR_MOTOR_H_
