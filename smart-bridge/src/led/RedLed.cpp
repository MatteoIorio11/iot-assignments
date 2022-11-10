#include "RedLed.h"
#include "Arduino.h"

#define TIME 2000

RedLed::RedLed(int pin){
    this->pin = pin;
    this->state = OFF;
}

void RedLed::init(){
    this->led = new Led(this->pin);
}

void RedLed::blink(){
    this->led->ledOn();
    delay(TIME);
    this->led->ledOff();
}

void RedLed::tick(){
    switch (this->state)
    {
        case ON:
            this->led->ledOn();
            break;
        case OFF:
            this->led->ledOff();
            break;
        case BLINKING:
            this->blink();
            break;
        case ALERT:
            this->led->ledOn();
            break;
            
    
    }
}

