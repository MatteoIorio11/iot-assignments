#include "WifiEsp.h"

/// @brief Constructor
WiFiEsp::WiFiEsp(){
    this->setup();
    this->connect();
}

/// @brief Setup of the Wifi
void WiFiEsp::setup(){
    WiFi.mode(WIFI_STA);
    WiFi.begin(this->ssid, this->password);
}

/// @brief Connect to the wifi
void WiFiEsp::connect(){
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        //Serial.print(".");
    }
    
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    
}




