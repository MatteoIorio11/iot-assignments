#include "PhotoResistor.h"
#include "Arduino.h"

PhotoResistor::PhotoResistor(int pin){
    this->pin = pin;
    pinMode(this->pin, INPUT);

}

double PhotoResistor::readValue(){
    int value = analogRead(A0);
    return ((double) value) * 5/1024;
}

int PhotoResistor::getPin(){
    return this->pin;
}