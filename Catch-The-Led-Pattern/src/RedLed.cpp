#include <Arduino.h>

class RedLed{

    private :
        int pin = 0;
        int status = LOW; 
        int fade = 0;
        int brightness = 0;
        int fadeAmount = 5;
    
    public : 
        RedLed(int input_pin){
            this->pin = input_pin;
        }
        
        void setFade(){
            analogWrite(this->pin, this->brightness);
            this->brightness = this->brightness + this->fadeAmount;
            if (this->brightness == 0 or this->brightness == 255){
                this->fadeAmount = -fadeAmount;
            }
        }

};