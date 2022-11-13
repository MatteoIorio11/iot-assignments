#ifndef __BUTTON__
#define __BUTTON__

#include "hardware/component/Button.h"

class Potentiometer: public Component{
    private:
        int pin;
    public:
        Potentiometer(int pin);
        int getPin();
        int readValue();
};

#endif