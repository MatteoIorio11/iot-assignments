#ifndef __JSONSERIALIZER__
#define __JSONSERIALIZER__
#include <ArduinoJson.h>
#define ARDUINO_TO_PC "Arduino"
#define PC_TO_ARDUINO "PC"
#define ANGLE_NOT_SET -1

class JsonSerializer{
    private:
        JsonSerializer();
    public:
        static void serializePreAlarm(double waterLevel);
        static void serializeAlarm(double waterLevel, int angle);
};

#endif