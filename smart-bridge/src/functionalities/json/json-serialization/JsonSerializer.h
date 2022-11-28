#ifndef __JSONSERIALIZER__
#define __JSONSERIALIZER__
#include <ArduinoJson.h>
#include "functionalities/waterflow-control-system/State.h"
#include "contants/Constants.h"

class JsonSerializer{
    private:
        JsonSerializer();
    public:
        static void serialize(WaterState state, double waterLevel, int angle, bool detected);
};

#endif