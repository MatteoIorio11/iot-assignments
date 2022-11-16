#include "JsonDeserializer.h"

int JsonDeserializer::getAngle(){
    String json = Serial.readString();  
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, json);
    const int angle = doc["angle"];

    return angle;
}