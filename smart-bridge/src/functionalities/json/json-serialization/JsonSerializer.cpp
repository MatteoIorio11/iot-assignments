#include "JsonSerializer.h"

void JsonSerializer::serialize(WaterState state, double waterLevel, int angle){
    
    String tagState = "\"waterState\":";
    String tagWater = ",\"waterLevel\":"; 
    String tagDegree = ",\"angle\":"; 
    String json =  
    OPEN_PARENTHESES +  
     tagState + state +
     tagWater + waterLevel + 
     tagDegree + angle + 
     CLOSE_PARENTHESES;
   /*
    DynamicJsonDocument doc(1024);
    doc["waterState"] = state;
    doc["waterLevel"] = waterLevel;
    doc["angle"] = angle;


    serializeJson(doc, Serial);
    
    String json = Serial.readString();
    */
    Serial.println(json);
}