#include "JsonSerializer.h"

void JsonSerializer::serialize(WaterState state, double waterLevel, int angle){
    DynamicJsonDocument doc(1024);
    doc["destination"] = ARDUINO_TO_PC;
    doc["waterState"] = state;
    doc["waterLevel"] = waterLevel;
    doc["angle"] = angle;

    serializeJson(doc, Serial);
    String a = Serial.readString();
    //serializeJson(doc, s, doc.size());
    Serial.println(a);
}