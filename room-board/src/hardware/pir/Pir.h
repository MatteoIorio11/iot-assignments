#ifndef __PIR__
#define __PIR__

#include <Arduino.h>
#include "hardware/hardware/Hardware.h"
#include "contants/Constants.h"

class Pir: public Hardware{
    private:
        int pin;
        void calibrate();
    public:
        Pir(int pin);
        int getPin();
        int readValue();
};

#endif