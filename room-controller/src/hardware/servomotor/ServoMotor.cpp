#include "ServoMotor.h"
#include "Arduino.h"

/// @brief constructor of the servomotor
/// @param pin 
ServoMotor::ServoMotor(int pin){
    this->pin = pin;
    this->servoMotor = new ServoTimer2();
    this->servoMotor->attach(this->pin);
    this->setOpening(0);
}
/// @brief set the input value as the current opening of the servo motor
/// @param percentage 
void ServoMotor::setOpening(int percentage){
    this->percentage = percentage;
    float coeff = ((float)FLAT_ANGLE_SERVO-(float)ZERO_SERVO)/FLAT_ANGLE;
    int new_angle= ZERO_SERVO + percentage*coeff;
    this->servoMotor->write(new_angle);    
}
/// @brief getter for the servo's opening
/// @return the percentage of the servo motor's opening
int ServoMotor::getOpening(){
    return this->percentage;
}
/// @brief fully close the sevo motor
void ServoMotor::close(){
    this->setOpening(0);    
}

/// @brief fully open the sevo motor
void ServoMotor::open(){
    this->setOpening(100);    
}