#ifndef __WIFIESP__
#define __WIFIESP__

#include <WiFi.h>
#include 

class WiFiEsp{
    private:
        char* ssid;
        char* password;
        void connect();
        void setup();
    public:
        WiFiEsp(char* ssid, char* psw);
};

#endif