#ifndef __REDLED__
#define __REDLED__

#include "task/Task.h"
#include "Led.h"

class RedLed : public Task{
    private:
        Led* led;
        int pin;
        enum {ON, OFF, BLINKING, ALERT} state;
        void blink();
    public:
        RedLed(int pin);
        void init();
        void tick();
};

#endif