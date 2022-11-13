#include "Potentiometer.h"
#include "Arduino.h"

Potentiometer::Potentiometer(int pin){
    this->pin = pin;
}

int Potentiometer::readValue(){
    int value = analogRead(A0);
    return map(value, 0, 1023, 0, 180);
}

int Potentiometer::getPin(){
    return this->pin;
}