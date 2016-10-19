#ifndef CONFIG_H
#define CONFIG_H

/* -- Loops -- */

#define LOOP_DURATION 200

/* -- Thresholds -- */

#define PIXY_THRESHOLD 20
#define COMPASS_THRESHOLD 5

/* -- Values -- */

/* Pixy */

#define PIXY_READ_TIME 50
#define PIXY_LED false

#define PIXY_ROTATE_FACTOR 16.0

#define PIXY_MIN_AREA 40

#define SHORT_HEIGHT 140
#define MEDIUM_HEIGHT 30
#define LONG_HEIGHT 20

/* Compass */

#define CORRECTION_ROTATION_MINIMUM 40
#define CORRECTION_ROTATION_MAXIMUM 80

#define COMPASS_CALIBRATION_TIME 1000

/* TSOPs */

#define TSOP_UPDATE 200

#define TSOP_NUM 12

#define TSOP_MINIMUM 5
#define TSOP_MAXIMUM 198

#define TSOP_K1 8
#define TSOP_K2 6
#define TSOP_K3 6

#define SHORT_STRENGTH 185
#define MEDIUM_STRENGTH 145

#define UNLOCK_DELAY 10000

/* Light Sensors */
#define LIGHT_SENSOR_CALIBRATION 15

/* Enables */

#define BLUETOOTH_ENABLED true
#define LIGHT_SENSORS_ENABLED true
#define PIXY_ENABLED true

/* Powers */

#define MAX_POWER 210
#define MEDIUM_POWER 170
#define MIN_POWER 130
#define EXTREME_MIN_POWER 80
#define WHITE_POWER 120
#define FRONT_POWER 230
#define MIN_FRONT_POWER 130

/* -- Debug -- */

#define LIGHT_SENSOR_DEBUG false

#define MOTOR_DEBUG false
#define MOTOR_VISUAL_DEBUG false

#define TSOP_DEBUG false
#define TSOP_DEBUG_UNFILTERED false
#define TSOP_VISUAL_DEBUG false

#define COMPASS_VISUAL_DEBUG false

#define PIXY_DEBUG false

#endif
