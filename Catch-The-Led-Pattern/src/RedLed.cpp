#include <Arduino.h>

class RedLed{

    private :
        int pin = 0;
        int status = LOW; 
        int brightness = 0;
        int fadeAmount = 5;
        bool on;
    
    public : 
        RedLed(int input_pin){
            this->pin = input_pin;
            this->on = true;
        }

        void setBrightness(){
            this->brightness = this->brightness + this->fadeAmount;
        }
        
        void setFade(){
            if(this->on){
                analogWrite(this->pin, this->brightness);
                delay(20);
                this->brightness = this->brightness + this->fadeAmount;
                if (this->brightness <= 0 or this->brightness >= 255){
                    this->fadeAmount = -fadeAmount;
                    Serial.println("FADE");
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
            analogWrite(this->pin, 0);
        }

        void setOn(){
            on = true;
            analogWrite(this->pin, 255);
        }

};