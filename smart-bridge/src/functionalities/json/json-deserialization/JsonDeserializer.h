#ifndef __JSONDESERIALIZER__
#define __JSONDESERIALIZER__
#include <ArduinoJson.h>
#include "functionalities/json/json-serialization/JsonSerializer.h"

class JsonDeserializer{
    private:
        JsonDeserializer();
    public:
        static int getAngle();
};

#endif