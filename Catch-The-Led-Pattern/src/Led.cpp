#include <Arduino.h>

class Led {
    protected : 
        int PIN = 0;
        int status = LOW;
        
        void setPin(int input_pin){
            this->PIN = input_pin;
        }
        
    public : 

        void setStatus(){
            this->status = !this->status;
        }
        int getPin(){
            return this->status;
        }

};
