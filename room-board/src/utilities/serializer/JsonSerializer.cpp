#include "JsonSerializer.h"
/*
TEMPLATE OF A SENDING JSON
{
  "who": "ESP32-S3",
  "detected":"true/false"
  "led_state": "ON/OFF"
}
*/
String JsonSerializer::serialize(LightSystemState state){

    DynamicJsonDocument doc(JSON_DIMENSION);
    doc["who"] = WHOIS;
    doc["detected"] = state == LED_ON; 
    doc["state"] = state == LED_ON ? "ON" : "OFF";
    char buffer[JSON_DIMENSION]; 
    serializeJson(doc, buffer); //serializing the JSON
    //String json = Serial.readString();
    return Converter::convertoArrayToString(buffer, JSON_DIMENSION);
}