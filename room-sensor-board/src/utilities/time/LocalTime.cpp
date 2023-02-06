#include "LocalTime.h"

String LocalTime::localTime(){
    struct tm timeinfo;
    const char* ntpServer = NTP_SERVER;
    const long  gmtOffset_sec = GMT_OFFSET;
    const int   daylightOffset_sec = DL_OFFSET;
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    if(!getLocalTime(&timeinfo)){
        return "-1";    //Something went wrong, I will continue to iterate the state machine and not trying to get the time
    }else{
        String time=String(timeinfo.tm_hour) + 
        ":" + (timeinfo.tm_min <= 9 ? "0"+String(timeinfo.tm_min) : String(timeinfo.tm_min)) +
        ":" + (timeinfo.tm_sec <= 9 ? "0"+String(timeinfo.tm_sec) : String(timeinfo.tm_sec));
        return time;
    }
}