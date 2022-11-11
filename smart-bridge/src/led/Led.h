#ifndef __LED__
#define __LED__

#include "task/Task.h"
#include "component/Component.h"

class Led: public Component{
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