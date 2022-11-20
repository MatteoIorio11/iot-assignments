#include "JsonDeserializer.h"

int JsonDeserializer::getAngle(bool control){
    String json = Serial.readString();
    if(!json.equals("")){
        int index = json.indexOf(':');
        String code = json.substring(1, index);
        if(code.equals("angle")){
            String angle_json = json.substring(index+2, json.length()-1);
            if(angle_json.equals("")){
                return -1;
            }else{
                return angle_json.toInt(); 
            }
        }else if(code.equals("control")){

        }
    }else{
        return -1;
    }
}