#ifndef __PHOTORESISTOR__
#define __PHOTORESISTOR__

#include <Arduino.h>
#include "hardware/hardware/SimpleHardware.h"

class Photoresistor: public SimpleHardware{
    private:
        int pin;
    public:
        Photoresistor(int pin);
        double readValue();
        int getPin();
};

#endif