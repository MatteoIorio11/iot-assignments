#include "Button.h"
#include "Arduino.h"

Button::Button(int pin){
    this->pin = pin;
}

int Button::getPin(){
    return this->pin;
}