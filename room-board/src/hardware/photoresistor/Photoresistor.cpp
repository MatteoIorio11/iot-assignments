#include "Photoresistor.h"

/// @brief Contructor of the Photoresistor
/// @param pin Photoresistor's pin
Photoresistor::Photoresistor(int pin){
    this->pin = pin;
}

/// @brief Get the Photoresistor's pin
/// @return Get the Photoresistor's pin
int Photoresistor::getPin(){
    return this->pin;
}

double Photoresistor::readValue(){
        int value = analogRead(this->pin);
    return ((double) value) * DIVISION_CONTANT;
}

