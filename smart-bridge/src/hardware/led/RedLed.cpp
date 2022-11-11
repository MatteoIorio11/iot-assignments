#include "RedLed.h"
#include "Arduino.h"

#define TIME 2000

RedLed::RedLed(int pin){
    this->pin = pin;
    this->state = OFF;
    pinMode(this->pin, OUTPUT);
}

void RedLed::init(){
    this->led = new Led(this->pin);
}

void RedLed::blink(){
    this->led->ledOn();
    delay(TIME);
    this->led->ledOff();
}

int RedLed::getPin(){
    return this->pin;
}
