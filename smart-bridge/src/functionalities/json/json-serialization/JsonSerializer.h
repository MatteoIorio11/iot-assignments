#ifndef __JSONSERIALIZER__
#define __JSONSERIALIZER__
#include <ArduinoJson.h>
#include "functionalities/waterflow-control-system/State.h"
#define ARDUINO_TO_PC "Arduino"
#define PC_TO_ARDUINO "PC"
#define ANGLE_NOT_SET -1

class JsonSerializer{
    private:
        JsonSerializer();
    public:
        static void serialize(WaterState state, double waterLevel, int angle);
};

#endif