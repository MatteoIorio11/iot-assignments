#ifndef __WIFIESP__
#define __WIFIESP__

#include <WiFi.h>
#include <Arduino.h>
#include "constants/Constants.h"
class WiFiEsp{
    private:
        const char* ssid = WIFI_SSID;
        const char* password = WIFI_PASSWORD;
        void connect();
        void setup();
    public:
        WiFiEsp();
};

#endif