#include "ServoMotor.h"
#include "Arduino.h"


ServoMotor::ServoMotor(int pin){
    this->pin = pin;
    this->servoMotor = new ServoTimer2();
    this->servoMotor->attach(this->pin);
    this->setAngle(0);
}

void ServoMotor::setAngle(int angle){
    float coeff = ((float)FLAT_ANGLE_SERVO-(float)ZERO_SERVO)/FLAT_ANGLE;
    int newAngle = ZERO_SERVO + angle*coeff;
    this->servoMotor->write(newAngle);    
}

int ServoMotor::getAngle(){
    return this->angle;
}
