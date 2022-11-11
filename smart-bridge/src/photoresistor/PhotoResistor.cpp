#include "PhotoResistor.h"
#include "Arduino.h"

PhotoResistor::PhotoResistor(int pin){
    this->pin = pin;
    pinMode(this->pin, INPUT);

}

int PhotoResistor::readValue(){
    int value = analogRead(this->pin);
    double valueInVolt = ((double) value) * 5/1024;
}

int PhotoResistor::getPin(){
    return this->pin;
}