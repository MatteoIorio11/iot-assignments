#ifndef __JSONSERIALIZER__
#define __JSONSERIALIZER__

#include <ArduinoJson.h>
#include "model/scheduler/tasks/LightSystemState.h"
#include "constants/Constants.h"

class JsonSerializer{
    private:
        JsonSerializer();
    public:
        static String serialize(LightSystemState status);
};

#endif