#include "ServoMotor.h"
#include "Arduino.h"


ServoMotor::ServoMotor(int pin){
    this->pin = pin;
    this->servoMotor = new ServoTimer2();
    this->servoMotor->attach(this->pin);
    this->setAngle(0);
}

void ServoMotor::setAngle(int angle){
    float coeff = (2250.0-750.0)/180;
    int newAngle = 750 + angle*coeff;
    this->servoMotor->write(newAngle);    
}

int ServoMotor::getAngle(){
    return this->angle;
}
