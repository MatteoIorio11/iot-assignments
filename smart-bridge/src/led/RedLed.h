#ifndef __REDLED__
#define __REDLED__

#include "task/Task.h"
#include "Led.h"

class RedLed{
    private:
        Led* led;
        int pin;
        enum {ON, OFF, BLINKING, ALERT} state;
    public:
        RedLed(int pin);
        void init();
        void blink();
        int getPin();
};

#endif