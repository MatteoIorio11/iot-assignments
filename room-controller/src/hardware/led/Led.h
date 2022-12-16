#ifndef __LED__
#define __LED__

#include <Arduino.h>
#include "hardware/hardware/Hardware.h"

class Led: public Hardware{
    private:
        int pin;
    public:
        Led(int pin);
        void ledOn();
        void ledOff();
        int getPin();
        int readValue();
};

#endif