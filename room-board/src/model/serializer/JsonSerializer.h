ifndef __JSONSERIALIZER__
#define __JSONSERIALIZER__

#include <ArduinoJson.h>
#include "constants/Constants.h"

class JsonSerializer{
    private:
        JsonSerializer();
    public:
        static void serialize();
};

#endif