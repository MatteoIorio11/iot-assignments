#include <Arduino.h>
class GreenLed {
    private :
        int pin = 0;
        int status = LOW;
    public : 
        GreenLed(int input_led){
            this->pin = input_led;   
        }
        void setStatus(){
            this->status = this->status == LOW ? HIGH : LOW;
        }
        int getPin(){
            return this->pin;
        }
};