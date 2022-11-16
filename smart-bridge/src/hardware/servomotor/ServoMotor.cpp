#include "ServoMotor.h"
#include "Arduino.h"


ServoMotor::ServoMotor(int pin){
    this->pin = pin;
    this->servoMotor = new ServoTimer2();
    this->servoMotor->attach(A1);
    this->setAngle(0);
}

void ServoMotor::setAngle(int angle){
    float coeff = (2250.0-750.0)/180;
    float a = 750 + angle*coeff;
    this->servoMotor->write(a);    

}

int ServoMotor::getAngle(){
    return this->angle;
}
