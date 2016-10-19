#include "LightSensor.h"

LightSensor::LightSensor(int in, int threshold) {
    inPin = in;
    thresholdValue = threshold;
}
void LightSensor::lightSensorSetup(){
    pinMode(inPin, INPUT);

    int calibrateTotal = 0;

    for (int i = 0; i < LS_CALIBRATE_COUNT; i++){
        read();
        calibrateTotal += readValue;
    }

    setThreshold((int)round((double)calibrateTotal/(double)LS_CALIBRATE_COUNT) + LS_BUFFER);
}

void LightSensor::read() {
    readValue = analogRead(inPin);
}

void LightSensor::setThreshold(int thresh) {
    thresholdValue = thresh;
}

bool LightSensor::isOnWhite() {
    read();
    return (readValue > thresholdValue);
}
