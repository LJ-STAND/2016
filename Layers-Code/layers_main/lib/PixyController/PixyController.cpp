#include "PixyController.h"

void PixyController::init() {
    pixy.init();
}

GoalPosition PixyController::getGoalPosition() {
    int blocks = pixy.getBlocks();

    if (blocks) {
        for (int i = 0; i < blocks; i++) {
            Block block = pixy.blocks[i];
            int area = block.width * block.height;

            if (area > PIXY_MIN_AREA && block.signature == 1) {
                lastGoalPosition = (GoalPosition) {(int) block.x, (int) block.y, (int) block.width, (int) block.height, true};
                return lastGoalPosition;
            }
        }
    }

    lastGoalPosition = (GoalPosition) {0, 0, 0, 0, false};
    return lastGoalPosition;
}

bool PixyController::isFacingGoal() {
    int difference = 160 - lastGoalPosition.x;

    return abs(difference) < PIXY_THRESHOLD;
}

bool PixyController::goalInSight() {
    return lastGoalPosition.goalInSight;
}
