#ifndef __JSONDESERIALIZER__
#define __JSONDESERIALIZER__
#include <ArduinoJson.h>
#include "contants/Constants.h"

class JsonDeserializer{
    private:
        JsonDeserializer();
    public:
        static int getAngle();
};

#endif