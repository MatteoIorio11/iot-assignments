#include "JsonSerializer.h"

void JsonSerializer::serializePreAlarm(double waterLevel){
    DynamicJsonDocument doc(1024);
    doc["waterLevel"] = waterLevel;

    serializeJson(doc, Serial);
}

void JsonSerializer::serializeAlarm(double waterLevel, int angle){
    DynamicJsonDocument doc(1024);
    doc["waterLevel"] = waterLevel;
    doc["angle"] = angle;

    serializeJson(doc, Serial);
}