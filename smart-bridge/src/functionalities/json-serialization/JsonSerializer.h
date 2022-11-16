#ifndef __JSONSERIALIZER__
#define __JSONSERIALIZER__
#include <ArduinoJson.h>

class JsonSerializer{
    private:
        JsonSerializer();
    public:
        static void serializePreAlarm(double waterLevel);
        static void serializeAlarm(double waterLevel, int angle);
};

#endif