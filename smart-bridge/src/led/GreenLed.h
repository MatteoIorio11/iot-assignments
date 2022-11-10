#include "Led.h"
#include "task/Task.h"
#ifndef __GREENLED__
#define __GREENLED__

class GreenLed : public Led, public Task{
    private:
        int pin;
        Led* led;
        enum {ON, OFF, ALERT} state;
    public:
        //Call the father's constructor 
        GreenLed(int pin) : Led(pin){}
        void init();
        void tick();
};

#endif