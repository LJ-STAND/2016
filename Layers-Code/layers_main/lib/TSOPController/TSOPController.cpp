#include "TSOPController.h"

TSOPController::TSOPController() {
    for (int i = 0; i < TSOP_NUM; i++) {
        pinMode(TSOPPins[i], INPUT);
    }

    pinMode(TSOP_POWER, OUTPUT);
    digitalWrite(TSOP_POWER, HIGH);
}

void TSOPController::updateValues() {
    for (int i = 0; i <= TSOP_NUM; i++) {
        TSOPValues[i] = TSOPValues[i] + (digitalRead(TSOPPins[i]) == HIGH ? 0 : 1);
    }
}

void TSOPController::update() {
    if (loopCount > TSOP_UPDATE) {
		loopCount = 0;

		bestTSOP();
		unlock();

		#if TSOP_VISUAL_DEBUG
			Bluetooth::send(String(tsopController.currentTSOP), BluetoothDataType::TSOP);
		#endif
	} else {
		loopCount++;

		updateValues();
	}
}

void TSOPController::bestTSOP() {
    bool isZero = true;
    int TSOPNum = 0;
    int bestValue = 0;
    int filteredValues[TSOP_NUM];

    #if TSOP_DEBUG
        String sendString = "";
    #endif

    for (int i = 0; i < TSOP_NUM; i++) {
        if (TSOPValues[i] < TSOP_MINIMUM || TSOPValues[i] > TSOP_MAXIMUM) {
            TSOPValues[i] = 0;
        }

        if (TSOPValues[i] != 0) {
            isZero = false;
        }

        filteredValues[i] = (TSOP_K1 * TSOPValues[i] + TSOP_K2 * (TSOPValues[mod(i - 1, TSOP_NUM)] + TSOPValues[mod(i + 1, TSOP_NUM)]) + TSOP_K3 * (TSOPValues[mod(i - 2, TSOP_NUM)] + TSOPValues[mod(i + 2, TSOP_NUM)])) /  (TSOP_K1 + TSOP_K2 + TSOP_K3);

        if (filteredValues[i] > bestValue) {
            bestValue = filteredValues[i];
            TSOPNum = i;
        }

        #if TSOP_DEBUG && TSOP_DEBUG_UNFILTERED
            sendString += String(TSOPValues[i]) + ", ";
        #elif TSOP_DEBUG
            sendString += String(filteredValues[i]) + ", ";
        #endif
    }

    for (int i = 0; i < TSOP_NUM; i++) {
        TSOPValues[i] = 0;
    }

    currentStrength = filteredValues[TSOPNum];
    currentTSOP = isZero ? -1 : TSOPNum;

    #if TSOP_DEBUG
        sendString += String(currentTSOP);
        Bluetooth::send(sendString);
    #endif
}

int TSOPController::ballDirection() {
    return currentTSOP == -1 ? currentTSOP : currentTSOP * 30;
}

void TSOPController::unlock() {
    digitalWrite(TSOP_POWER, LOW);
    delayMicroseconds(UNLOCK_DELAY);
    digitalWrite(TSOP_POWER, HIGH);
}

bool TSOPController::holdingBall() {
    if (tsopController.currentTSOP == 0 && tsopController.currentStrength > SHORT_STRENGTH) {
        return true;
    } else {
        return false;
    }
}
