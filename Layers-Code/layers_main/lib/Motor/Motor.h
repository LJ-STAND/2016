#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>
#include <Bluetooth.h>
#include <Config.h>

class Motor {
public:
	int n = 0;
	int motorAngle;

	Motor() {}
	Motor(int pwm, int inOne, int inTwo, int standby, int angle, bool reverse = false);

	void set(int power);
	void brake();

private:
	int pwmPin;
	int inOnePin;
	int inTwoPin;
	int standbyPin;
	bool reversed;
};

#endif
