/* Master program for J STAND 2016
 * By Sam Tudor
 * Copyright 2016 Sam Tudor
 */

#include <motor.h> // done but untested
#include <jstandcommon.h>
#include <motorarray.h> // done but untested
//#include <lightsensor.h> // need to do
#include <tsoparray.h> // works
#include <I2C.h>
#include <compass.h> // works?
#include <defines.h>
#include <LightSensorArray.h>

#include "arduino.h"

//=====MOTORS=====//

/* motor 1 = front-right
 * motor 2 = back-right
 * motor 3 = back-left
 * motor 4 = front-left
 */ // not this

/* motor 1 = front-right
 * motor 2 = back
 * motor 3 = front-left
 */

 // moving the motor 100 is clockwise for all motors

MotorArray motors = MotorArray();


//=====LIGHT SENSORS=====//

LightSensorArray lights = LightSensorArray();


//=====TSOPS=====//

/* tsop 0 = straight forward
 * tsop 1 = 30 degree bearing clockwise
 * so on
 * tsop 11 = 330 degree bearing clockwise (30 degree bearing anticlockwise)
 */

TsopArray tsops = TsopArray();


//=====COMPASS=====//

Compass compass = Compass();


//=====EVERYTHING ELSE=====//

typedef struct dirSpeed{
    int dir;
    int speed;
};


dirSpeed avoidLineDirection(dirSpeed orbit, LineLocation lineLocation, int lineMag) {
    int direction = orbit.dir;
    int speed = orbit.speed;
    double correctedDirection = (double)direction;
    int correctedSpeed = LINE_AVOID_SPEED;


    switch (lineLocation) {
        case LineLocation::left:
            if (direction >= 270) {
                // correctedDirection = 10;
                correctedDirection = lineMag * LS_URGENCY;
            } else if (direction < 270 && direction >= 180) {
                // correctedDirection = 170;
                correctedDirection = 180 - lineMag * LS_URGENCY;
            }

            break;

        case LineLocation::right:
            if (direction <= 90) {
                // correctedDirection = 350;
                correctedDirection = 360 - lineMag * LS_URGENCY;
            } else if (direction > 90 && direction <= 180) {
                // correctedDirection = 190;
                correctedDirection = 180 + lineMag * LS_URGENCY;
            }

            break;

        case LineLocation::front:
            if (direction <= 90) {
                // correctedDirection = 100;
                correctedDirection = 90 + lineMag * LS_URGENCY;
            } else if (direction >= 270) {
                // correctedDirection = 260;
                correctedDirection = 270 - lineMag * LS_URGENCY;
            }

            break;

        case LineLocation::back:
            if (direction < 180 && direction >= 90) {
                // correctedDirection = 80;
                correctedDirection = 90 - lineMag * LS_URGENCY;
            } else if (direction >= 180 && direction <= 270) {
                // correctedDirection = 280;
                correctedDirection = 270 + lineMag * LS_URGENCY;
            }

            break;

        case LineLocation::cornerBackLeft:
            if (direction >= 90 && direction < 225) {
                // correctedDirection = 80;
                correctedDirection = 90 - lineMag * LS_URGENCY;
            } else if (direction >= 225) {
                correctedDirection = 10;
            }

            break;

        case LineLocation::cornerBackRight:
            if (direction <= 270 && direction > 135) {
                // correctedDirection = 280;
                correctedDirection = 270 + lineMag * LS_URGENCY;
            } else if (direction <= 135) {
                correctedDirection = 350;
            }

            break;

        case LineLocation::cornerFrontLeft:
            if (direction <= 90 || direction > 315) {
                // correctedDirection = 100;
                correctedDirection = 90 + lineMag * LS_URGENCY;
            } else if (direction <= 315 && direction >= 180) {
                correctedDirection = 10;
            }

            break;

        case LineLocation::cornerFrontRight:
            if (direction >= 270 || direction < 45) {
                // correctedDirection = 260;
                correctedDirection = 270 - lineMag * LS_URGENCY;
            } else if (direction >= 45 && direction <= 180) {
                correctedDirection = 190;
            }

            break;

        case LineLocation::field:
            correctedSpeed = speed;
            break;
    }

    dirSpeed corrected = {(int)round(correctedDirection), correctedSpeed};
    return corrected;
}

dirSpeed orbitDirection(int tsopAngle){
    // decides the orbit direction based purely off ball direction and angle
    // int angle = mod((int)round(tsopAngle) - 10, 360); // this function seems to need an offset otherwise it doesn't work, could be a dead tsop
    int angle = tsopAngle;
    int returnAngle;
    if(angle < SMALL_ANGLE || angle > 360 - SMALL_ANGLE){
         returnAngle = (int)round(angle < 180 ? (angle * 0.5) : (180 + angle * 0.5));
    }
    else if(angle < BIG_ANGLE || angle > 360 - BIG_ANGLE){
        if (angle < 180){
            double nearFactor = (double)(angle - SMALL_ANGLE) / (double)(BIG_ANGLE - SMALL_ANGLE);
            returnAngle = (int)round(90 * nearFactor);
        }else{
            double nearFactor = (double)(360 - angle - SMALL_ANGLE) / (double)(BIG_ANGLE - SMALL_ANGLE);
            returnAngle =  (int)round(360 - (90 * nearFactor));
        }
    }
    else{
        if (tsops.strength > SHORT_STRENGTH) {
            returnAngle =  angle + (angle < 180 ? 90 : -90);
        } else if (tsops.strength > MEDIUM_STRENGTH) {
            double strengthFactor = (double)(tsops.strength - MEDIUM_STRENGTH) / (double)(SHORT_STRENGTH - MEDIUM_STRENGTH);
            double angleFactor = strengthFactor * 90;

            returnAngle = mod(angle + (angle < 180 ? angleFactor : -angleFactor), 360);
        } else {
            returnAngle = angle;
        }
    }
    dirSpeed orbit = {returnAngle, NORMAL_SPEED};
    return orbit;
}

int compassCorrection() {
    // reads the compass object and finds the heading of the robot and returns the corrective rotation
    int correct;
    int heading  = 360 - compass.heading; // our compass is on upside down now
    if(heading < 180){
        correct = (int)round(-heading * COMPASS_CORRECT_MAG);
    }else{
        correct = (int)round((360 - heading) * COMPASS_CORRECT_MAG);
    }
    return correct;
}

void moveDecide(){
    dirSpeed orbit = orbitDirection(tsops.angle);
    dirSpeed avoid = avoidLineDirection(orbit, lights.lineLocation, lights.lineMag);

    int comp = compassCorrection();
    int avoidDir = avoid.dir;
    int avoidSpeed = avoid.speed;
    #if DEBUG_ENABLED_NORMAL
        // Serial.println(compass.heading);

        Serial.println();

        Serial.println(tsops.angle);
        Serial.println(tsops.strength);

        Serial.println();

        // Serial.println(lights.lsFront);
        // Serial.println(lights.lsRight);
        // Serial.println(lights.lsLeft);
        //
        // Serial.println();


        Serial.println(orbit.dir);

        Serial.println();

        // Serial.println(comp);
        //
        // Serial.println();
        //
        // Serial.println(avoidDir);
        // Serial.println(avoidSpeed);

        Serial.println();
        Serial.println();
    #endif

    if(tsops.angle != -1){
        // if (avoidDir != orbit){
            #if LS_ENABLED
                motors.moveDirection(avoidDir, avoidSpeed, comp); // avoid light, orbit and compass correct
            #else
                motors.moveDirection(orbit.dir, orbit.speed, comp);
            #endif

            // if (avoid != orbit){
            //     delay(LS_DELAY);
            // }
        // }
        // else{
        //     motors.moveDirection(orbit, NORMAL_SPEED, comp); // orbit and compass correct
        // }

    }else{
        motors.moveDirection(0, 0, comp); // compass correct
    }
}


void setup() {
    // empty
    Wire.begin();
    #if DEBUG_ENABLED_ANY
        Serial.begin(9600);
    #endif
    tsops.tsopArraySetup();
    compass.compassSetup();
    motors.MotorArraySetup();
    lights.LightSensorArraySetup();

    motors.brake();
    compass.calibrate();

}


void loop() {
    tsops.updateOnce();
    // if (tsops.tsopCounter % 64 == 0){
    //
    // }
    if (tsops.tsopCounter >= READ_NUM) {
        compass.updateGyro();
        lights.updateLineLocation();
        tsops.finishRead();
        tsops.unlockTsops();
        moveDecide();




        #if DEBUG_ENABLED_NORMAL
            delay(1000);
        #endif

    }
}
