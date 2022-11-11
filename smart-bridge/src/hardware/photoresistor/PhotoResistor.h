#ifndef __PHOTORESISTOR__
#define __PHOTORESISTOR__

#include "hardware/component/Component.h"

class PhotoResistor: public Component{
    private:
        int pin;
    public:
        PhotoResistor(int pin);
        int readValue();
        int getPin();
};

#endif