#include "LightSensor.h"

LightSensor::LightSensor(int in) {
    inPin = in;
    pinMode(in, INPUT);
}

void LightSensor::calibrate() {
    int defaultValue;

    for (int i = 0; i < 10; i++) {
        defaultValue += read();
    }

    defaultValue /= 10;
    thresholdValue = defaultValue + LIGHT_SENSOR_CALIBRATION;

    Bluetooth::send(String(thresholdValue));
}

int LightSensor::read() {
    return analogRead(inPin);
}

bool LightSensor::isOnWhite() {
    if (read() > thresholdValue) {
        return true;
    } else {
        return false;
    }
}
