#ifndef __JSONSERIALIZER__
#define __JSONSERIALIZER__

#include <ArduinoJson.h>
#include "model/scheduler/tasks/LightSystemState.h"
#include "hardware/led/LedState.h"
#include "constants/Constants.h"
#include "utilities/converter/Converter.h"
#include "utilities/time/LocalTime.h"

class JsonSerializer{
    private:
        JsonSerializer();
    public:
        static String serialize(LightSystemState status, LedState ledState);
};

#endif