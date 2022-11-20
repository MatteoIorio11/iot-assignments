#include "JsonDeserializer.h"

int JsonDeserializer::getAngle(){
    String json = Serial.readString();
    if(!json.equals("")){
        int index = json.indexOf(':');
        String code = json.substring(1, index+1);
        if(code.indexOf('a') >= 0){
            String angle_json = json.substring(index+2, json.length()-1);
            if(angle_json.equals("")){
                return -1;
            }else{
                int angle =  angle_json.toInt(); 
                if(angle >= 0){
                    return angle;
                }else{
                    return -2;
                }
            }
        }
    }else{
        return -1;
    }
}