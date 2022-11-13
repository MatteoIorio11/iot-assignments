#ifndef __POTENTIOMETER__
#define __POTENTIOMETER__

#include "hardware/component/Component.h"

class Potentiometer: public Component{
    private:
        int pin;
    public:
        Potentiometer(int pin);
        int readValue();
};

#endif