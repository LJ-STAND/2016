#ifndef MATHS_H
#define MATHS_H

#include <Arduino.h>
#include <math.h>

double degreesToRadians(double degrees);
double radiansToDegrees(double radians);
int mod(int value, int mod);
double doubleAbs(double value);
double doubleMod(double value, double maxValue);
double doubleMax(double v1, double v2);

#endif
