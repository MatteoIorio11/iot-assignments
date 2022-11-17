#include "ServoMotor.h"
#include "Arduino.h"


ServoMotor::ServoMotor(int pin){
    this->pin = pin;
    this->servoMotor = new ServoTimer2();
    this->servoMotor->attach(this->pin);
    this->setAngle(0);
}

void ServoMotor::setAngle(int angle){
    float coeff = (2300.0-550.0)/180;
    int newAngle = 550 + angle*coeff;
    this->servoMotor->write(newAngle);    
}

int ServoMotor::getAngle(){
    return this->angle;
}
