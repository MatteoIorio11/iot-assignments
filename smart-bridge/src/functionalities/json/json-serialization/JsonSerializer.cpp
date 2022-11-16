#include "JsonSerializer.h"

void JsonSerializer::serializePreAlarm(double waterLevel){
    DynamicJsonDocument doc(1024);
    doc["destination"] = ARDUINO_TO_PC;
    doc["waterLevel"] = waterLevel;
    doc["angle"] = ANGLE_NOT_SET;


    serializeJson(doc, Serial);
}

void JsonSerializer::serializeAlarm(double waterLevel, int angle){
    DynamicJsonDocument doc(1024);
    doc["destination"] = ARDUINO_TO_PC;
    doc["waterLevel"] = waterLevel;
    doc["angle"] = angle;

    serializeJson(doc, Serial);
}