#include "MotorTI.h"

MotorTI::MotorTI(int pwm, int dir, int brk, int angle, bool reverse) {
	pwmPin = pwm;
	dirPin = dir;
	brkPin = brk;
	motorAngle = angle;
	reversed = reverse;

	pinMode(pwm, OUTPUT);
	pinMode(dir, OUTPUT);
	pinMode(brk, OUTPUT);
}

void MotorTI::set(int power) {
	if (power > 0) {
		analogWrite(pwmPin, constrain(power, 0, 255));

		if (reversed) {
			digitalWrite(dirPin, LOW);
			digitalWrite(brkPin, LOW);
		} else {
			digitalWrite(dirPin, HIGH);
			digitalWrite(brkPin, LOW);
		}
	} else if (power < 0) {
		analogWrite(pwmPin, constrain(abs(power), 0, 255));

		if (reversed) {
			digitalWrite(dirPin, HIGH);
			digitalWrite(brkPin, LOW);
		} else {
			digitalWrite(dirPin, LOW);
			digitalWrite(brkPin, LOW);
		}
	} else {
		analogWrite(pwmPin, 255);
		digitalWrite(dirPin, HIGH);
		digitalWrite(brkPin, HIGH);
	}
}

void MotorTI::brake() {
	set(0);
}
