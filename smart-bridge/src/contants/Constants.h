#ifndef __CONSTANTS__
#define __CONSTANTS__
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://
// PINS OF THE HARDWARE 

#define PIN_LED_SLS 12
#define PIN_GREENLED_WCS 11
#define PIN_REDLED_WCS 10
#define PIN_SONAR 9
#define PIN_SONAR_TRG 8
#define PIN_BUTTON 6
#define PIN_PIR 2
#define PIN_PHOTORESISTOR A0
#define PIN_SERVO_MOTOR A1
#define PIN_POTENTIOMETER A2
#define PERIOD 100
#define MONITOR_ADDRESS 0x27
#define ROWS 20
#define COLS 4

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://
// TIMER COSTANTS

#define NORMAL_STATE_SAMPLING pow(10, 6)
#define PREALARM_STATE_SAMPLING pow(10, 6)/2
#define ALARM_STATE_SAMPLING pow(10, 6)/4

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://
// PIR CONSTANTS

#define CALIBRATION_TIME_SEC 20

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://
// SERVO MOTOR CONSTANTS

#define ZERO_SERVO 550
#define FLAT_ANGLE_SERVO 2300
#define FLAT_ANGLE 180

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://
// WATER FLOW WATER SYSTEM CONSTANTS

#define MINIMUM_SONAR_DISTANCE (float)0.001
#define WL2_BOUND (float)0.3
#define WL1_BOUND (float)0.9
#define MAXIMUM_SONAR_DISTANCE (float)1.00

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://
// JSON DESERIALIZATION CONSTANTS

#define CODE_EMPTY_MESSAGE -1
#define CODE_SWITCH_CONTROL -2

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://
// JSON SERIALIZATION CONSTANTS

#define ARDUINO_TO_PC "Arduino"
#define OPEN_PARENTHESES "{"
#define CLOSE_PARENTHESES "}"
#define PC_TO_ARDUINO "PC"
#define ANGLE_NOT_SET -1

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://
// LOGIC SMART LIGHT SYSTEM CONSTANTS

#define LUMINOSITY_LOWERBOUND (float)2
//The timer1 is ten seconds based on the period
#define TIMER_T1(p) (pow(10,7)/(p))

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://
// LOGIC WATER FLOW CONTROL SYSTEM CONSTANTS

#define BLINK_2SEC(p) ((pow(10,6))/(p))

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://


#endif