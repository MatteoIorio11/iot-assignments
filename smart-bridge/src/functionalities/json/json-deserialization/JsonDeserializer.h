#ifndef __JSONDESERIALIZER__
#define __JSONDESERIALIZER__
#include <ArduinoJson.h>
#include "functionalities/json/json-serialization/JsonSerializer.h"

#define CODE_EMPTY_MESSAGE -1
#define CODE_SWITCH_CONTROL -2

class JsonDeserializer{
    private:
        JsonDeserializer();
    public:
        static int getAngle();
};

#endif