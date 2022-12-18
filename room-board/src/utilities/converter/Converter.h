#ifndef __CONVERTER__
#define __CONVERTER__

#include <Arduino.h>

class Converter{
    private:
        Converter();
    public:
        static String convertoArrayToString(char* array, int size);
};

#endif