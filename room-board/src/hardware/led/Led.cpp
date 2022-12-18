#include "Led.h"

/// @brief Constructor of the Led;
/// @param pin Led's pin
Led::Led(int pin){
    this->pin = pin;
    this->state = LED_OFF;
    pinMode(this->pin, OUTPUT);
}

/// @brief Turn on the led
void Led::ledOn(){
    this->state = LED_ON;
    digitalWrite(this->pin, HIGH);
}

/// @brief Turn Off the led
void Led::ledOff(){
    this->state = LED_OFF;
    digitalWrite(this->pin, LOW);
}


/// @brief Get the Led's pin
/// @return Get the Led's pin
int Led::getPin(){
    return this->pin;
}

/// @brief Understand if the led is on or off
/// @return Get the value read from the esp
int Led::readValue(){
    return digitalRead(this->pin);
}

LedState Led::getState(){
    return this->state;
}