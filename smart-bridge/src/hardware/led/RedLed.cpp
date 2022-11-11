#include "RedLed.h"
#include "Arduino.h"

#define TIME 2000

RedLed::RedLed(int pin){
    this->pin = pin;
    this->state = OFF;
    pinMode(this->pin, OUTPUT);
}

void RedLed::blink(){
    this->ledOn();
    delay(TIME);
    this->ledOff();
}

int RedLed::getPin(){
    return this->pin;
}
