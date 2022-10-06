#include <Arduino.h>
#include "Led.cpp"

class GreenLed : public Led{
    public : 
        GreenLed(int intput_led){
            Led::setPin(intput_led);   
        }
};