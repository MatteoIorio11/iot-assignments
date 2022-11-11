#ifndef __REDLED__
#define __REDLED__

#include "task/Task.h"
#include "Led.h"

class RedLed: public Led{
    private:
        int pin;
        enum {ON, OFF, BLINKING, ALERT} state;
    public:
        RedLed(int pin);
        void blink();
        int getPin();
        int readValue();
};

#endif