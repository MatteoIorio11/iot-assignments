#include "Button.h"
#include "Arduino.h"
/// @brief constructor for the button
/// @param pin 
Button::Button(int pin){
    this->pin = pin;
    pinMode(this->pin, INPUT);
}
/// @brief getter for the pin's button
/// @return the pin of the button 
int Button::getPin(){
    return this->pin;
}