#include <Arduino.h>

class RedLed{

    private :
        int pin = 0;
        int status = LOW; 
        int fade = 0;
        int brightness = 0;
        int fadeAmount = 5;
        bool on = true;
    
    public : 
        RedLed(int input_pin){
            this->pin = input_pin;
        }
        
        void setFade(){
            if(on){
                analogWrite(this->pin, this->brightness);
                this->brightness = this->brightness + this->fadeAmount;
                if (this->brightness == 0 or this->brightness == 255){
                    this->fadeAmount = -fadeAmount;
                }
            }
        }

        int getPin(){
            return this->pin;
        }

        int getBrightness(){
            return this->brightness;
        }

        int getFade(){
            return this->fadeAmount;
        }

        void setOff(){
            on = false;
        }

        void setOn(){
            on = true;
        }

};