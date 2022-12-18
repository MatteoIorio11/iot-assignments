#include "Photoresistor.h"

/// @brief Contructor of the Photoresistor
/// @param pin Photoresistor's pin
Photoresistor::Photoresistor(int pin){
    this->pin = pin;
    pinMode(this->pin, INPUT);
}

/// @brief Get the Photoresistor's pin
/// @return Get the Photoresistor's pin
int Photoresistor::getPin(){
    return this->pin;
}

/// @brief Read the value from the Photoresistor, used in order to understand if the led must go ON or OFF
/// @return return the value in voltage read from the photoresistor
double Photoresistor::readValue(){
    int value = analogRead(this->pin);
    return ((double) value) * 5/1024;
}

