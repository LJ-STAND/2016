#include "Maths.h"

double degreesToRadians(double degrees) {
    return degrees * ((double) PI / 180.0);
}

double radiansToDegrees(double radians) {
    return radians * ((180.0 / (double) PI));
}

int mod(int value, int mod) {
    int r = value % mod;
    return r < 0 ? r + mod : r;
}

double doubleAbs(double value) {
    if (value > 0) {
        return value;
    } else {
        return -value;
    }
}

double doubleMod(double value, double maxValue) {
    return fmod((value + maxValue), maxValue);
}

double doubleMax(double v1, double v2) {
    return v1 > v2 ? v1 : v2;
}
