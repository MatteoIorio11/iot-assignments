#ifndef __CONSTANTS__
#define __CONSTANTS__

#define WHOIS "Romm Sensor-Board"

// ==================================================================
// PIR'S CONSTANTS:

#define PIN_PIR 48
#define CALIBRATION_TIME_SEC 1

// ==================================================================

// ==================================================================
// PHOTORESISTOR'S CONSTANTS:

#define PIN_PHOTORESISTOR 11
#define LUMINOSITY_LOWERBOUND (double)2.5
#define DIVISION_CONSTANT 5/1024
// ==================================================================

// ==================================================================
// LED'S CONSTANTS:

#define PIN_LED 7

// ==================================================================

// ==================================================================
// SCHEDULER'S CONSTANTS:

#define MAX_TASKS 10

// ==================================================================


// ==================================================================
// MQTT'S CONSTANTS:

#define MQTT_PORT 1883
#define MQTT_SERVER "broker.mqtt-dashboard.com"
#define MQTT_MSG_MAX_SIZE 256
#define MQTT_TOPIC "esp-light"
#define MQTT_CLIENTNAME "esp32-s3-"

// ==================================================================


// ==================================================================
// WIFI'S CONSTANTS:

#define WIFI_SSID "TIM-27646389"
#define WIFI_PASSWORD "i5mESEIA5DcTznCk7CssfAXv"
#define WIFI_NTPSERVER "pool.ntp.org"


// ==================================================================

// ==================================================================
// LOCALTIME'S CONSTANTS:

#define NTP_SERVER "pool.ntp.org"
#define GMT_OFFSET 3600
#define DL_OFFSET 0

// ==================================================================


// ==================================================================
// JSONSERIALIZER'S CONSTANTS:

#define JSON_DIMENSION 128

// ==================================================================

// ==================================================================
// TIMER'S CONSTANTS:

#define TIMER_PERIOD pow(10,5)

// ==================================================================


#endif
