#ifndef PIXYCONTROLLER_H
#define PIXYCONTROLLER_H

#include <Arduino.h>
#include <Config.h>
#include <Bluetooth.h>
#include <Pixy.h>
#include <SPI.h>
#include <GoalPosition.h>
#include <Maths.h>

class PixyController {
public:
    GoalPosition lastGoalPosition;

    PixyController() {};

    void init();
    GoalPosition getGoalPosition();
    bool isFacingGoal();
    bool goalInSight();

private:
    int n = 0;

    Pixy pixy;
};

extern PixyController pixyController;

#endif
