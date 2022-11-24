#include "JsonDeserializer.h"

int JsonDeserializer::getAngle(){
    String json = Serial.readString();

    if(!json.equals("")){
        DynamicJsonDocument doc(256);
        deserializeJson(doc, json);
        int angle = doc["angle"];
        Serial.println(angle);
        if(angle >= 0){
            return angle;
        }else{
            return CODE_SWITCH_CONTROL;
        }
        return angle;
    }else{
        return CODE_EMPTY_MESSAGE;
    }
    
}