#include "MotorController.h"

MotorController::MotorController() {
    motorLeft = Motor(MOTOR_LEFT_PWM, MOTOR_LEFT_IN1, MOTOR_LEFT_IN2, MOTOR_LEFT_SB, 60, true);
    motorRight = Motor(MOTOR_RIGHT_PWM, MOTOR_RIGHT_IN1, MOTOR_RIGHT_IN2, MOTOR_RIGHT_SB, 300, true);
    motorBack = Motor(MOTOR_BACK_PWM, MOTOR_BACK_IN1, MOTOR_BACK_IN2, MOTOR_BACK_SB, 180, true);
}

void MotorController::move(int direction, int power, LineLocation lineLocation, int rotation) {
    direction = avoidLine(direction, lineLocation);

    if (lineLocation != LineLocation::field) {
        if (!isOnLine) {
            isOnLine = true;
            power = 0;
        }

        power = WHITE_POWER;
    } else {
        isOnLine = false;
    }

    if (direction != lastDirection || rotation != lastRotation || power != lastPower) {
        lastDirection = direction;
        lastRotation = rotation;
        lastPower = power;

        double directionAngleRadians = degreesToRadians(360 - direction);

        double motorLeftValue = cos(degreesToRadians(motorLeft.motorAngle + 90) - directionAngleRadians);
        double motorRightValue = cos(degreesToRadians(motorRight.motorAngle + 90) - directionAngleRadians);
        double motorBackValue = cos(degreesToRadians(motorBack.motorAngle + 90) - directionAngleRadians);

        double updatedPower = (double) power / doubleAbs(fmax(fmax(doubleAbs(motorLeftValue), doubleAbs(motorRightValue)), doubleAbs(motorBackValue)));

        int motorLeftPower = (int) round(motorLeftValue * updatedPower) + rotation;
        int motorRightPower = (int) round(motorRightValue * updatedPower) + rotation;
        int motorBackPower = (int) round(motorBackValue * updatedPower) + rotation;

        #if MOTOR_DEBUG
            Bluetooth::send("Left: " + String(motorLeftPower) + " Right: " + String(motorRightPower) + " Back: " + String(motorBackPower) + " Direction: " + String(direction) + " Power: " + String(power));
        #endif

        #if MOTOR_VISUAL_DEBUG
    		Bluetooth::send(String(abs(motorLeftPower)), BluetoothDataType::motorLeft);
            Bluetooth::send(String(abs(motorRightPower)), BluetoothDataType::motorRight);
            Bluetooth::send(String(abs(motorBackPower)), BluetoothDataType::motorBack);
    	#endif

        motorLeft.set(motorLeftPower);
        motorRight.set(motorRightPower);
        motorBack.set(motorBackPower);
    }
}

void MotorController::moveToBall(int ballDirection, int strength, LineLocation lineLocation, int rotation) {
    if (ballDirection != lastBallDirection || strength != lastStrength) {
        lastBallDirection = ballDirection;
        lastStrength = strength;

        if (ballDirection == 0) {
            if (pixyController.goalInSight() && pixyController.lastGoalPosition.height < MEDIUM_HEIGHT) {
                move(ballDirection, MIN_FRONT_POWER, lineLocation, rotation);
            } else if (pixyController.goalInSight() && pixyController.isFacingGoal()) {
                move(ballDirection, FRONT_POWER, lineLocation, rotation);
            } else {
                move(ballDirection, MIN_FRONT_POWER, lineLocation, rotation);
            }
        } else if (ballDirection == 180) {
            if (lineLocation == LineLocation::left || lineLocation == LineLocation::cornerBackLeft) {
                move(270, MAX_POWER, lineLocation, rotation);
            } else {
                move(90, MAX_POWER, lineLocation, rotation);
            }
        } else {
            if (lineLocation == LineLocation::back) {
                if (ballDirection >= 90 && ballDirection < 180) {
                    move(90, constrain(MAX_POWER, 0, 255 - rotation), lineLocation, rotation);
                } else if (ballDirection >= 180 && ballDirection <= 270) {
                    move(270, constrain(MAX_POWER, 0, 255 - rotation), lineLocation, rotation);
                }
            } else if (strength > SHORT_STRENGTH) {
                double strengthFactor;

                if (ballDirection >= 180) {
                    strengthFactor = 1.0 - ((ballDirection - 180) / 180);
                } else {
                    strengthFactor = ballDirection / 180;
                }

                if (ballDirection == 330 || ballDirection == 30) {
                    move(mod(ballDirection + (ballDirection < 180 ? 40 : -40), 360), constrain(EXTREME_MIN_POWER + (strengthFactor * (MIN_POWER - EXTREME_MIN_POWER)), 0, 255 - rotation), lineLocation, rotation);
                } else {
                    move(mod(ballDirection + (ballDirection < 180 ? 90 : -90), 360), constrain(EXTREME_MIN_POWER + (strengthFactor * (MIN_POWER - EXTREME_MIN_POWER)), 0, 255 - rotation), lineLocation, rotation);
                }
            } else if (strength > MEDIUM_STRENGTH) {
                double strengthFactor = (strength - (double) MEDIUM_STRENGTH) / (double)(SHORT_STRENGTH - MEDIUM_STRENGTH);
                double angleFactor = strengthFactor * 90;

                move(mod(ballDirection + (ballDirection < 180 ? angleFactor : -angleFactor), 360), constrain(MAX_POWER - (strengthFactor * (MAX_POWER - MEDIUM_POWER)), 0, 255 - rotation), lineLocation, rotation);
            } else {
                move(ballDirection, constrain(MAX_POWER, 0, 255 - rotation), lineLocation, rotation);
            }
        }
    } else {
        move(lastDirection, lastPower, lineLocation, rotation);
    }
}

void MotorController::rotate(int power) {
    motorLeft.set(power);
    motorRight.set(power);
    motorBack.set(power);
}

void MotorController::brake() {
    motorLeft.brake();
    motorRight.brake();
    motorBack.brake();
}

int MotorController::avoidLine(int direction, LineLocation lineLocation) {
    int correctedDirection = direction;

    switch (lineLocation) {
        case LineLocation::left:
            if (direction >= 270) {
                correctedDirection = 20;
            } else if (direction < 270 && direction >= 180) {
                correctedDirection = 160;
            }

            break;

        case LineLocation::right:
            if (direction <= 90 || direction >= 340) {
                correctedDirection = 340;
            } else if (direction > 90 && direction <= 200) {
                correctedDirection = 200;
            }

            break;

        case LineLocation::front:
            if (direction <= 110) {
                correctedDirection = 110;
            } else if (direction >= 250) {
                correctedDirection = 250;
            }

            break;

        case LineLocation::frontMiddle:
            correctedDirection = 180;

            break;

        case LineLocation::back:
            if (direction < 180 && direction >= 70) {
                correctedDirection = 70;
            } else if (direction >= 180 && direction <= 290) {
                correctedDirection = 290;
            }

            break;

        case LineLocation::cornerBackLeft:
            if (direction >= 70 && direction < 225) {
                correctedDirection = 70;
            } else if (direction >= 225 || direction <= 20) {
                correctedDirection = 20;
            }

            break;

        case LineLocation::cornerBackRight:
            if (direction <= 290 && direction > 135) {
                correctedDirection = 290;
            } else if (direction <= 135 || direction >= 340) {
                correctedDirection = 340;
            }

            break;

        case LineLocation::cornerFrontLeft:
            if (direction <= 110 || direction > 315) {
                correctedDirection = 110;
            } else if (direction <= 315 && direction >= 180) {
                correctedDirection = 160;
            }

            break;

        case LineLocation::cornerFrontRight:
            if (direction >= 250 || direction < 45) {
                correctedDirection = 250;
            } else if (direction >= 45 && direction <= 200) {
                correctedDirection = 200;
            }

            break;

        case LineLocation::field:
            break;
    }

    return correctedDirection;
}
