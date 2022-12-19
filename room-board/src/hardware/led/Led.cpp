#include "Led.h"

/// @brief Constructor of the Led;
/// @param pin Led's pin
Led::Led(int pin){
    this->pin = pin;
    this->state = LED_OFF;
    pinMode(this->pin, OUTPUT);
}

/// @brief Turn on the led
void Led::turnOn(){
    this->state = LED_ON;
    digitalWrite(this->pin, HIGH);
}

/// @brief Turn Off the led
void Led::turnOff(){
    this->state = LED_OFF;
    digitalWrite(this->pin, LOW);
}

// ::::::::::::::::::::::::::::::::: START MANAGE THE ROOM CONTROLLER'S LED
/// @brief Change the state of the led to ON
void Led::stateOn(){
    this->state = LED_ON;
}
/// @brief Change the state of the led to OFF
void Led::stateOff(){
    this->state = LED_OFF;
}
// ::::::::::::::::::::::::::::::::: END MANAGE THE ROOM CONTROLLER'S LED


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