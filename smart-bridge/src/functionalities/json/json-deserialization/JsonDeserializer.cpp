#include "JsonDeserializer.h"

int JsonDeserializer::getAngle(){
    String json = Serial.readString();
    if(!json.equals("")){
        int index = json.indexOf(':');
        String angle_json = json.substring(index+2, json.length()-1);
        if(angle_json.equals("")){
            return CODE_EMPTY_MESSAGE;
        }else{
            int angle =  angle_json.toInt(); 
            if(angle >= 0){
                return angle;
            }else{
                return CODE_SWITCH_CONTROL;
            }
        }
    }else{
        return CODE_EMPTY_MESSAGE;
    }
}