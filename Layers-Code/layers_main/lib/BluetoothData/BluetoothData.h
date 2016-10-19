#ifndef BLUETOOTHDATA_H
#define BLUETOOTHDATA_H

enum BluetoothDataType: int {
    TSOP,
    info,
    heading,
    motorLeft,
    motorRight,
    motorBack,
    none
};

typedef struct BluetoothData {
    BluetoothDataType type;
    int value;
} BluetoothData;

#endif
