#ifndef __JSONSERIALIZER__
#define __JSONSERIALIZER__

#include <ArduinoJson.h>
#include "model/scheduler/tasks/RoomControllerState.h"
#include "constants/Constants.h"

class JsonSerializer{
    private:
        JsonSerializer();
    public:
        static String serialize(RoomControllerState status);
};

#endif