#include "ServoMotor.h"
#include "Arduino.h"
#include <Servo.h>

ServoMotor::ServoMotor(int pin){
    this->pin = pin;
    this->servoMotor->attach(pin);
    this->setAngle(0);
}

void ServoMotor::setAngle(int angle){
    this->angle = angle;
    this->servoMotor->write(angle);
}

int ServoMotor::getAngle(){
    return this->angle;
}
