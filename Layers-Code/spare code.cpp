void pixyData() {
	uint16_t blocks = pixy.getBlocks();

    if (blocks) {
        Block block = pixy.blocks[0];

        if ((block.signature == 1 && GOAL_TYPE == GoalType::blue) || (block.signature == 2 && GOAL_TYPE == GoalType::yellow)) {
            int blockMinX = block.x - (block.width / 2);
            int blockMaxX = block.x + (block.width / 2);

            if (compass.heading < 180) {
                if (blockMinX > PIXY_THRESHOLD) {
                    motorController.goDirection(270, blockMinX * 5, lineLocation, -50);
                } else {
                    motorController.goDirection(0, 200, lineLocation);
                }
            } else if (compass.heading >= 180) {
                if (blockMaxX < 319 - PIXY_THRESHOLD) {
                    motorController.goDirection(90, blockMinX * 5, lineLocation, 50);
                } else {
                    motorController.goDirection(0, 200, lineLocation);
                }
            }
        } else {
            rotateToGoal();
        }
    } else {
        rotateToGoal();
    }
}

void rotateToGoal() {
	int rotationZ = compass.readMagnetometer().z;

    if (rotationZ < 360 - COMPASS_TOLERANCE && rotationZ >= 180) {
        motorController.goDirection(270, (rotationZ - 180) * 5, lineLocation, 50);
    } else if (rotationZ > COMPASS_TOLERANCE && rotationZ < 180) {
        motorController.goDirection(90, (rotationZ - 180) * 5, lineLocation, 50);
    } else {
        motorController.brake();
    }
}
