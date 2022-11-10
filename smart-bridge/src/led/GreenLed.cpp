#include "GreenLed.h"
#include "Arduino.h"

GreenLed::GreenLed(int pin) : Led(pin){
    //Calling the father constructor
}

void GreenLed::tick(){
    switch (this->state)
    {
        case ON:
            this->ledOn();
            break;
        case OFF:
            this->ledOff();
            break;
    
    }
}

void GreenLed::init(){

}