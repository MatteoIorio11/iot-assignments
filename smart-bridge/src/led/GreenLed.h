#include "Led.h"
#ifndef __GREENLED__
#define __GREENLED__

class GreenLed : public Led{
    private:
        int pin;
        enum {ON, OFF, ALERT} state;
    public:
        //Call the father's constructor 
        GreenLed(int pin);
        void ledOn();
        void ledOff();
};

#endif