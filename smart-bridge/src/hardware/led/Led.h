#ifndef __LED__
#define __LED__

#include "task/Task.h"
#include "hardware/component/Component.h"

class Led: public Component{
    private:
        int pin;
    public:
        void ledOn();
        void ledOff();
        int getPin();
};

#endif