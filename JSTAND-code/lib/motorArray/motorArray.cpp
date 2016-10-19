/* Library to calculate omnidrive direction for 4 wheeled robot with motor configuration of: {60,120,240,300}.
 * (or 3 wheel, 60, 180, 240)
 * Given speed, angle and rotation required.
 * Values are calculated on the spot, however this library is untested and precalculated values may be faster if well optimized.
 */

#include "motorarray.h"

#include <jstandcommon.h>

MotorArray::MotorArray(){
}

void MotorArray::MotorArraySetup(){
    motor1 = Motor(STANDBY_1, INONE_1, INTWO_1, PWM_1, ANGLE_1, REVERSED_1);
    motor2 = Motor(STANDBY_2, INONE_2, INTWO_2, PWM_2, ANGLE_2, REVERSED_2);
    motor3 = Motor(STANDBY_3, INONE_3, INTWO_3, PWM_3, ANGLE_3, REVERSED_3);
    motor1.motorSetup();
    motor2.motorSetup();
    motor3.motorSetup();
}

void MotorArray::updateDirection(int angle, int speed, int rotate){
    if (angle != currentAngle || speed != currentSpeed || rotate != currentRotate){
        moveDirection(angle, speed, rotate);
    }
}

void MotorArray::moveDirection(int angle, int speed, int rotate) {

    double directionAngleRadians = degreesToRadians(angle/* + 180*/);

    double values[MOTOR_NUM] = {
        cos(degreesToRadians(motor1.getAngle() + 90) - directionAngleRadians),
        cos(degreesToRadians(motor2.getAngle() + 90) - directionAngleRadians),
        cos(degreesToRadians(motor3.getAngle() + 90) - directionAngleRadians)/*,
        cos(degreesToRadians(motor4.getAngle() + 90) - directionAngleRadians)*/
    };

    double maxValue = (double)max(doubleAbs(values[0]), max(doubleAbs(values[1]), doubleAbs(values[2])));

    double realPower = (double)speed/(double)(maxValue);

    // float updatedPower = (speed * 255) / (maxSpeed * doubleAbs(max(max(doubleAbs(values[0]), doubleAbs(values[1])), doubleAbs(values[2])))); // Missing a bit for 4 motors

    for (int i = 0; i < MOTOR_NUM; i++) values[i] = round((values[i] * realPower)) + rotate;

    // maxValue = (double)max(doubleAbs(values[0]), max(doubleAbs(values[1]), doubleAbs(values[2])));
    //
    // for (int i = 0; i < MOTOR_NUM; i++) values[i] *= (double)255 / maxValue;
    // Serial.println(values[0]);
    // Serial.println(values[1]);
    // Serial.println(values[2]);

    motor1.move(constrain((int)round(values[0]), -255, 255), 255);
    motor2.move(constrain((int)round(values[1]), -255, 255), 255);
    motor3.move(constrain((int)round(values[2]), -255, 255), 255);
}

void MotorArray::brake(){
    motor1.move(0);
    motor2.move(0);
    motor3.move(0);
}
