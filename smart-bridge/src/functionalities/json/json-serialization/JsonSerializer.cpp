#include "JsonSerializer.h"
/*
TEMPLATE OF A SENDING JSON
{
  "waterState": x,
  "waterLevel"; y,
  "angle": z
}
*/
void JsonSerializer::serialize(WaterState state, double waterLevel, int angle){
    /*
    String tagState = "\"waterState\":";
    String tagWater = ",\"waterLevel\":"; 
    String tagDegree = ",\"angle\":"; 
    String json =  
    OPEN_PARENTHESES +  
     tagState + state +
     tagWater + waterLevel + 
     tagDegree + angle + 
     CLOSE_PARENTHESES;
   */
    DynamicJsonDocument doc(256);
    doc["waterState"] = state;
    doc["waterLevel"] = waterLevel;
    doc["angle"] = angle;
    serializeJson(doc, Serial); //serializing the JSON
    String json = Serial.readString();  
    Serial.println(json); //sending the JSON to the PC
}