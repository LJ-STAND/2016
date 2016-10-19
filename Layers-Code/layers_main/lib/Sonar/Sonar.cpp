#include "Sonar.h"

Sonar::Sonar(int trig, int echo) {
    trigPin = trig;
    echoPin = echo;

    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);
}

int Sonar::read() {
    long duration, distance;

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);

    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration / 2) / 29.1;

    return (int)distance;
}
