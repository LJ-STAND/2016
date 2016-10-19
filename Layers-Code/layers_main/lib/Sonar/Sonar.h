#ifndef SONAR_H
#define SONAR_H

#include <Arduino.h>

class Sonar {
public:
    Sonar() {}
    Sonar(int trig, int echo);

    int read();

private:
    int trigPin;
    int echoPin;
};

#endif
