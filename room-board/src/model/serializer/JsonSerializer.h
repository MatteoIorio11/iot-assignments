ifndef __JSONSERIALIZER__
#define __JSONSERIALIZER__

#include <ArduinoJson.h>
#include "model/scheduler/tasks/LightSystemStatus.h"
#include "constants/Constants.h"

class JsonSerializer{
    private:
        JsonSerializer();
    public:
        static void serialize(LightSystemStatus status);
};

#endif