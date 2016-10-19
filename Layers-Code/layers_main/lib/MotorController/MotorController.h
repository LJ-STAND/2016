#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include <Arduino.h>
#include <Motor.h>
#include <Pins.h>
#include <Maths.h>
#include <LineLocation.h>
#include <Vector3D.h>
#include <Bluetooth.h>
#include <TSOPController.h>
#include <Config.h>
#include <PixyController.h>

class MotorController {
public:
    Motor motorLeft;
    Motor motorRight;
    Motor motorBack;

    MotorController();

    void move(int direction, int power, LineLocation lineLocation = LineLocation::field, int rotation = 0);
    void moveToBall(int ballDirection, int strength, LineLocation lineLocation = LineLocation::field, int rotation = 0);
    void rotate(int power);
    void brake();
    int avoidLine(int direction, LineLocation lineLocation);

private:
    int lastDirection;
    int lastRotation;
    int lastPower;
    int lastBallDirection;
    int lastStrength;

    bool isOnLine = false;
};

extern MotorController motorController;

#endif
