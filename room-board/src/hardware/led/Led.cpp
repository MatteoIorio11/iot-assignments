#include "Led.h"

/// @brief Constructor of the Led;
/// @param pin Led's pin
Led::Led(int pin){
    this->pin = pin;
}

/// @brief Turn on the led
void Led::ledOn(){
    digitalWrite(this->pin, HIGH);
}

/// @brief Turn Off the led
void Led::ledOff(){
    digitalWrite(this->pin, LOW);
}


/// @brief Get the Led's pin
/// @return Get the Led's pin
int Led::getPin(){
    return this->pin;
}

int Led::readValue(){
    return digitalRead(this->pin);
}