#include <Arduino.h>
#include <Bluetooth.h>
#include <Compass.h>
#include <Config.h>
#include <LightSensorController.h>
#include <LineLocation.h>
#include <Maths.h>
#include <MotorController.h>
#include <Pins.h>
#include <PixyController.h>
#include <Sonar.h>
#include <TSOPController.h>

/* ---- Won Nationals!!! --- */
/* ----------- :) ---------- */

/* -- Sensors & Controllers -- */

MotorController motorController;
TSOPController tsopController;
LightSensorController lightSensorController;
PixyController pixyController;

Compass compass;

/* -- Counters -- */

int TSOPCount;
int loopCount;
bool blinkOn;

unsigned long lastPixyTime;

/* -- Functions -- */

int correctionRotation() {
	double relativeHeading = compass.relativeHeading();

	int correctionRotation;

	if (abs(relativeHeading) > COMPASS_THRESHOLD) {
		correctionRotation = (int) relativeHeading;

		if (correctionRotation < 0 && correctionRotation > -CORRECTION_ROTATION_MINIMUM) {
			correctionRotation = -CORRECTION_ROTATION_MINIMUM;
		} else if (correctionRotation > 0 && correctionRotation < CORRECTION_ROTATION_MINIMUM) {
			correctionRotation = CORRECTION_ROTATION_MINIMUM;
		} else if (correctionRotation > 0 && correctionRotation > CORRECTION_ROTATION_MAXIMUM) {
			correctionRotation = CORRECTION_ROTATION_MAXIMUM;
		} else if (correctionRotation < 0 && correctionRotation < -CORRECTION_ROTATION_MAXIMUM) {
			correctionRotation = -CORRECTION_ROTATION_MAXIMUM;
		}
	} else {
		correctionRotation = 0;
	}

	return correctionRotation;
}

void move() {
	int moveRotation = correctionRotation();

	if (tsopController.currentTSOP == -1) {
		motorController.rotate(moveRotation);
	} else {
		motorController.moveToBall(tsopController.ballDirection(), tsopController.currentStrength, lightSensorController.lineLocation, moveRotation);
	}
}

void blinkLED() {
    if (loopCount < LOOP_DURATION) {
        loopCount++;
    } else {
        loopCount = 0;
        blinkOn = !blinkOn;

		#if !PIXY_LED
	        digitalWrite(LED_BUILTIN, blinkOn ? HIGH : LOW);
		#endif
	}
}

void pixyData() {
	GoalPosition goalPosition = pixyController.getGoalPosition();

	#if PIXY_DEBUG
		Bluetooth::send(String(goalPosition.goalInSight));
	#endif

	if (goalPosition.goalInSight) {
		#if PIXY_LED
			digitalWrite(LED_BUILTIN, HIGH);
		#endif

		int difference = 160 - goalPosition.x;
		double amount = abs(difference - PIXY_THRESHOLD) / PIXY_ROTATE_FACTOR;

		if (abs(compass.relativeHeading() < COMPASS_THRESHOLD)) {
			if (difference > PIXY_THRESHOLD) {
				compass.facingDirection = doubleMod(compass.facingDirection - amount, 360);
			} else if (difference < -PIXY_THRESHOLD) {
				compass.facingDirection = doubleMod(compass.facingDirection + amount, 360);
			}
		} else {
			if (difference <= PIXY_THRESHOLD) {
				compass.facingDirection = compass.heading;
			}
		}
	} else {
		#if PIXY_LED
			digitalWrite(LED_BUILTIN, LOW);
		#endif

		compass.facingDirection = 0.0;
	}
}

void pixyTimerUpdate() {
	int timeSinceLast = (int)((double)(micros() - lastPixyTime) / 1000.0);

	if (timeSinceLast > PIXY_READ_TIME) {
		pixyData();
		lastPixyTime = micros();
	}
}

void setup() {
	Wire.begin();

	pinMode(LED_BUILTIN, OUTPUT);

	Serial.begin(9600);

	compass.init();
	compass.calibrate();

	#if BLUETOOTH_ENABLED
		Bluetooth::init();
	#endif

	#if LIGHT_SENSORS_ENABLED
		lightSensorController.calibrate();
	#endif

	#if PIXY_ENABLED
		pixyController.init();

		lastPixyTime = micros();
	#endif
}

void loop() {
	if (loopCount % 10 == 0) {
		compass.updateGyro();

		#if COMPASS_VISUAL_DEBUG
			Bluetooth::send(String(compass.heading), BluetoothDataType::heading);
		#endif
	}

	#if PIXY_ENABLED
		pixyTimerUpdate();
	#endif

	tsopController.update();
	lightSensorController.updateLineLocation();

	move();

	blinkLED();
}
