#include "Potentiometer.h"
#include "Arduino.h"
/// @brief constructor for the potentiometer
/// @param pin 
Potentiometer::Potentiometer(int pin){
    this->pin = pin;
    pinMode(this->pin, INPUT);
}
/// @brief reads the value from the potentiometer
/// @return the actual value of the potentiometer
int Potentiometer::readValue(){
    int value = analogRead(this->pin);
    return map(value, 0, 1023, 0, 180);
}
/// @brief getter for the pin of the potentiometer
/// @return the pin of the potentiometer 
int Potentiometer::getPin(){
    return this->pin;
}