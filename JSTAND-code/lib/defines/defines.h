#ifndef LIB_DEFINES_DEFINES_H_
#define LIB_DEFINES_DEFINES_H_


//=====GENERAL=====//

#define DEBUG_ENABLED_NORMAL false
#define DEBUG_ENABLED_ANY false
#define LS_ENABLED true


//=====MOTORS====//

#define PWM_1 2
#define STANDBY_1 26
#define INONE_1 22
#define INTWO_1 24
#define ANGLE_1 60
#define REVERSED_1 false

#define PWM_2 3
#define STANDBY_2 32
#define INONE_2 28
#define INTWO_2 30
#define ANGLE_2 180
#define REVERSED_2 true

#define PWM_3 4
#define STANDBY_3 38
#define INONE_3 34
#define INTWO_3 36
#define ANGLE_3 300
#define REVERSED_3 true

/* #define PWM_4 2
#define STANDBY_4 23
#define INONE_4 22
#define INTWO_4 1
#define ANGLE_4 300
#define REVERSED_4 -1 */

#define MOTOR_NUM 3


//=====LIGHT SENSORS=====//

#define LS_LEFT_OUTER A0
#define LS_LEFT_MIDDLE A1
#define LS_LEFT_INNER A2
#define LS_FRONT_OUTER A6
#define LS_FRONT_MIDDLE A5
#define LS_FRONT_INNER A4
#define LS_RIGHT_OUTER A3
#define LS_RIGHT_MIDDLE A7
#define LS_RIGHT_INNER A8

#define DEFAULT_LS_THRESHOLD 350

#define LS_BUFFER 20

#define LS_CALIBRATE_COUNT 10

#define LS_DELAY 400

#define LS_URGENCY 7.5


//=====TSOPS=====//
// Oh god I love memes

#define TSOP_0 31
#define TSOP_1 33
#define TSOP_2 35
#define TSOP_3 37
#define TSOP_4 39
#define TSOP_5 41
#define TSOP_6 43
#define TSOP_7 45
#define TSOP_8 23
#define TSOP_9 25
#define TSOP_10 27
#define TSOP_11 29

#define UNLOCK_PIN 53


// K1 + 2 * K2 + 2 * K3 = 16
#define TSOP_K1 12
#define TSOP_K2 1
#define TSOP_K3 1

#define TSOP_NUM 12
#define READ_NUM 255
#define UNLOCK_DELAY 1
#define MIN_IGNORE_TSOPS 5
#define MAX_IGNORE_TSOPS 200
#define BEST_TSOP_NO_ANGLE 3
#define BEST_TSOP_NO_STRENGTH 1

#define FIRST_TSOP_WEIGHT 3
#define SECOND_TSOP_WEIGHT 2

#define TSOP_FILTER_NOISE true
#define TSOP_FILTER_SURROUNDING true


//====COMPASS====//

#define COMPASS_CALIBRATION 1.39
#define COMPASS_CALIBRATION_TIME 1000
#define COMPASS_CORRECT_MAG 1.5


//====ORBIT====//

#define SHORT_STRENGTH 135
#define MEDIUM_STRENGTH 110

#define SMALL_ANGLE 5
#define BIG_ANGLE 20

#define NORMAL_SPEED 170
#define LINE_AVOID_SPEED 160

#endif  // LIB_DEFINES_DEFINES_H_
