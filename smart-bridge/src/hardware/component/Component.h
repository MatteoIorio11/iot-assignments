#ifndef __COMPONENT__
#define __COMPONENT__

#include "SimpleComponent.h"

class Component: public SimpleComponent{
    private:
        int pin;
    public:
        int getPin();
        int readValue();
};

#endif