#include "ServoMotor.h"
#include "Arduino.h"


ServoMotor::ServoMotor(int pin){
    this->pin = pin;
    this->servoMotor = new ServoTimer2();
    this->servoMotor->attach(this->pin);
    this->setAngle(0);
}

void ServoMotor::setAngle(int angle){
    this->angle = angle;
    float coeff = ((float)FLAT_ANGLE_SERVO-(float)ZERO_SERVO)/FLAT_ANGLE;
    int new_angle= ZERO_SERVO + angle*coeff;
    this->servoMotor->write(new_angle);    
}

int ServoMotor::getAngle(){
    return this->angle;
}
