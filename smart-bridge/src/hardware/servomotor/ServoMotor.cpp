#include "ServoMotor.h"
#include "Arduino.h"

/// @brief constructor of the servomotor
/// @param pin 
ServoMotor::ServoMotor(int pin){
    this->pin = pin;
    this->servoMotor = new ServoTimer2();
    this->servoMotor->attach(this->pin);
    this->setAngle(0);
}
/// @brief set the input value as the current angle of the servo motor
/// @param angle 
void ServoMotor::setAngle(int angle){
    this->angle = angle;
    float coeff = ((float)FLAT_ANGLE_SERVO-(float)ZERO_SERVO)/FLAT_ANGLE;
    int new_angle= ZERO_SERVO + angle*coeff;
    this->servoMotor->write(new_angle);    
}
/// @brief getter for the servo's angle
/// @return the servo motor's angle
int ServoMotor::getAngle(){
    return this->angle;
}
