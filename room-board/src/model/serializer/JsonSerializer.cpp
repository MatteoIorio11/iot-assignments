#include "JsonSerializer.h"
/*
TEMPLATE OF A SENDING JSON
{
  "waterState": w,
  "waterLevel"; x,
  "angle": y,
  "led": z
}
*/
void JsonSerializer::serialize(){

    DynamicJsonDocument doc(256);
    doc["waterState"] = state == NORMAL ? "Normal State" : state == PRE_ALARM ? "Pre Alarm State" : "Alarm state"; 
    doc["waterLevel"] = waterLevel;
    doc["angle"] = angle;
    doc["led"] = detected == true ? "ON" : "OFF";
    serializeJson(doc, Serial); //serializing the JSON
    String json = Serial.readString();  
    Serial.println(json); //sending the JSON to the PC
}