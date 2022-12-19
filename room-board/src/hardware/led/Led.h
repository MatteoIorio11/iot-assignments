#ifndef __LED__
#define __LED__

#include <Arduino.h>
#include "hardware/hardware/Hardware.h"
#include "LedState.h"

class Led: public Hardware{
    private:
        int pin;
        LedState state;
    public:
        Led(int pin);
        void changeState();
        void turnOn();
        void turnOff();
        int getPin();
        int readValue();
        LedState getState();
};

#endif