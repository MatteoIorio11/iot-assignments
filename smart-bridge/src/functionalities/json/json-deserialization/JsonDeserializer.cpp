#include "JsonDeserializer.h"
/*
TEMPLATE OF RECEIVING JSON
this could be extended with more parameters in the future
{
    "angle": x
}
*/

/*
__Old version for the deserialization__

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
*/
int JsonDeserializer::getAngle(){
    String json = Serial.readString(); //reading the JSON from the serial

    if(!json.equals("")){
        DynamicJsonDocument doc(256);
        deserializeJson(doc, json); //deserializing of te JSON
        int angle = doc["angle"]; //getting the angle
        if(angle >= 0){
            return angle;
        }else{ 
            //if the angle is less than 0 this means that we want to switch the control from the pc to the potentiometer.
            return CODE_SWITCH_CONTROL;
        }
    }else{
        return CODE_EMPTY_MESSAGE;
    }
    
}