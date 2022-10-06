#include <Arduino.h>
#include "Led.cpp"

class RedLed : public Led {

    private : 
        int fade = 0;
        int brightness = 0;
        int fadeAmount = 5;
    
    public : 
        RedLed(int input_pin){
            Led::setPin(input_pin);
        }
        void setFade(){
            analogWrite(this->PIN, brightness);
            brightness = brightness + fadeAmount;
            if (brightness == 0 || brightness == 255){
                fadeAmount = -fadeAmount;
            }
        }

};