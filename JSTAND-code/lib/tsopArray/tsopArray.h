/* Library for interfacing with tsop array
 */

#ifndef LIB_TSOPARRAY_TSOPARRAY_H_
#define LIB_TSOPARRAY_TSOPARRAY_H_

#include "arduino.h"

// #include "jstandcommon.h"
#include <defines.h>

// class Tsop {
//  public:
//     Tsop(int pinVal);
//     Tsop(){}
//     void tsopSetup();
//     void readOnce();
//     void setValueZero();
//     int getValue();
//     int getPin();
//  private:
//     int pin,value;
// };

class TsopArray {
 public:
    TsopArray();
    void tsopArraySetup();
    void updateOnce();
    void on();
    void off();
    void unlockTsops();
    void finishRead();
    void sortFilterValues();
    void getAngleSimple();
    void getAngle(int n);
    void getStrengthSimple();
    void getStrength(int n);

    int tempValues[TSOP_NUM] = {0};
    int values[TSOP_NUM] = {0};
    int tempFilteredValues[TSOP_NUM] = {0};
    int filteredValues[TSOP_NUM] = {0};
    int sortedFilteredValues[TSOP_NUM] = {0};
    int indexes[TSOP_NUM] = {0};
    int tsopCounter = 0;
    int angle = 0;
    int simpleAngle = 0;
    int strength = 0;
    int simpleStrength = 0;
 public:
     int tsopPins[TSOP_NUM] = {TSOP_0, TSOP_1, TSOP_2, TSOP_3, TSOP_4, TSOP_5, TSOP_6, TSOP_7, TSOP_8, TSOP_9, TSOP_10, TSOP_11};
     int scaledSin[TSOP_NUM] = {0};
     int scaledCos[TSOP_NUM] = {0};
};

#endif  // LIB_TSOPARRAY_TSOPARRAY_H_
