#include "GreenLed.h"
#include "Arduino.h"

GreenLed::GreenLed(int pin){
    this->pin = pin;
    pinMode(this->pin, OUTPUT);
}
void GreenLed::init(){
    this->led = new Led(this->pin);
    this->state = OFF;  
}

void GreenLed::tick(){
    switch (this->state)
    {
        case ON:
            this->led->ledOn();
            break;
        case OFF:
            this->led->ledOff();
            break;
        case ALERT:
            this->led->ledOff();
            break;
    }
}

