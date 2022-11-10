#ifndef __LED__
#define __LED__

#include "task/Task.h"

class Led{
        int pin;
    public:
        Led(int pin);
        void ledOn();
        void ledOff();
};

#endif