#ifndef __LOCALTIME__
#define __LOCALTIME__
#include <time.h>
#include <Arduino.h>
#include "constants/Constants.h"

class LocalTime{
    private:
        LocalTime();
    public:
        static String localTime();
};

#endif