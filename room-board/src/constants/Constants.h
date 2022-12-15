#ifndef __CONSTANTS__
#define __CONSTANTS__

#define WHOIS "ESP32-S3"

// ==================================================================
// PIR'S CONSTANTS:

#define PIN_PIR 48
#define CALIBRATION_TIME_SEC 1

// ==================================================================

// ==================================================================
// PHOTORESISTOR'S CONSTANTS:

#define PIN_PHOTORESISTOR 11
#define LUMINOSITY_LOWERBOUND (double)2
#define DIVISION_CONTANT (double)5/1024
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

// ==================================================================


#endif
