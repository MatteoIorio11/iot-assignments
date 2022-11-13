#ifndef __BUTTON__
#define __BUTTON__

#include "hardware/component/SimpleComponent.h"

class Button: public SimpleComponent{
    private:
        int pin;
    public:
        Button(int pin);
        int getPin();
};

#endif