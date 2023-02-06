#ifndef __HARDWARE__
#define __HARDWARE__

#include "SimpleHardware.h"

class Hardware: public SimpleHardware{
    private:
        int pin;
    public:
        int getPin();
        int readValue();
};

#endif