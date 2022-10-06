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
            analogWrite(this->PIN, this->brightness);
            this->brightness = this->brightness + this->fadeAmount;
            if (this->brightness == 0 or this->brightness == 255){
                this->fadeAmount *= -1;
            }
        }

};