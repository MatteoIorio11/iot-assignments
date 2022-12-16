#include "LocalTime.h"

String LocalTime::localTime(){
    struct tm timeinfo;

    String time ="";
    if(!getLocalTime(&timeinfo)){
        Serial.println("Failed to obtain time");
        return time;
    }else{

        return time;
    }
}