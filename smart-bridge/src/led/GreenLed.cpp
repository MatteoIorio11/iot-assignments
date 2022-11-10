#include "GreenLed.h"
#include "Arduino.h"

GreenLed::GreenLed(int pin){
    this->pin = pin;
    pinMode(this->pin, OUTPUT);
}

void GreenLed::ledOn(){
    digitalWrite(this->pin, HIGH);
}

void GreenLed::ledOff(){
    digitalWrite(this->pin, LOW);
}
