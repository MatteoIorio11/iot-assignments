#include "JsonSerializer.h"

void JsonSerializer::serializePreAlarm(double waterLevel){
    DynamicJsonDocument doc(1024);
    doc["sewaterLevel"] = waterLevel;

    serializeJson(doc, Serial);
}