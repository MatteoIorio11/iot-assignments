#include "JsonSerializer.h"
/*
TEMPLATE OF A SENDING JSON
{
  "who": "ESP32-S3",
  "state"; "DETECTED/NOT_DETECTED"
}
*/
String JsonSerializer::serialize(LightSystemState state){
    DynamicJsonDocument doc(256);
    doc["who"] = WHOIS;
    doc["state"] = state == DETECTED ? "DETECTED" : "NOT_DETECTED"; 
    serializeJson(doc, Serial); //serializing the JSON
    String json_serialized = Serial.readString();  
    return json_serialized;
}