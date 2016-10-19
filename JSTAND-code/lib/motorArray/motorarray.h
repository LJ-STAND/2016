
/* Library to calculate omnidrive direction for 4 wheeled robot with motor configuration of: {60,120,240,300}.
 * Given speed, angle and rotation required.
 * Values are precalculated to save time by avoiding trig calculations, however this library is untested and on-the-spot calculation may be faster if well optimized.
 */

#ifndef LIB_MOTORARRAY_MOTORARRAY_H_
#define LIB_MOTORARRAY_MOTORARRAY_H_

#include "arduino.h"

#include <motor.h>
// #include <jstandcommon.h>
#include <defines.h>


class MotorArray{
 public:
    MotorArray();

    void moveDirection(int angle, int speed, int rotate);
    void updateDirection(int angle, int speed, int rotate);
    void MotorArraySetup();
    void brake();

 // private:
     Motor motor1/* = Motor(STANDBY_1, INONE_1, INTWO_1, PWM_1, ANGLE_1, REVERSED_1)*/;
     Motor motor2/* = Motor(STANDBY_2, INONE_2, INTWO_2, PWM_2, ANGLE_2, REVERSED_2)*/;
     Motor motor3/* = Motor(STANDBY_3, INONE_3, INTWO_3, PWM_3, ANGLE_3, REVERSED_3)*/;
     // Motor motor4 = Motor(STANDBY_4, INONE_4, INTWO_4, PWM_4, ANGLE_4, REVERSED_4);
     int currentAngle = 0;
     int currentSpeed = 0;
     int currentRotate = 0;

};

#endif  // LIB_MOTORARRAY_MOTORARRAY_H_
