#ifndef __PIR__
#define __PIR__

#include "hardware/component/Component.h"
#include "contants/Constants.h"

class Pir: public Component{
    private:
        int pin;
    public:
        Pir(int pin);
        void calibrate();
        int readValue();
        int getPin();
};

#endif