#ifndef MOTORTI_H
#define MOTORTI_H

#include "Arduino.h"
#include "Math.h"

class MotorTI {
public:
	int motorAngle;

	MotorTI() {}
	MotorTI(int pwm, int direction, int brake, int angle, bool reverse = false);
	void set(int power);
	void brake();

private:
	int pwmPin;
	int dirPin;
	int brkPin;
	bool reversed;
};

#endif
