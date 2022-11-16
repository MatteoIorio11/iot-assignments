#include "Button.h"
#include "Arduino.h"

Button::Button(int pin){
    this->pin = pin;
    pinMode(this->pin, INPUT);
}

int Button::getPin(){
    return this->pin;
}