#ifndef __PHOTORESISTOR__
#define __PHOTORESISTOR__

#include "hardware/component/SimpleComponent.h"

class PhotoResistor: public SimpleComponent{
    private:
        int pin;
    public:
        PhotoResistor(int pin);
        double readValue();
        int getPin();
};

#endif