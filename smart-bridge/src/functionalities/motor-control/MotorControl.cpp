#include "MotorControl.h"
#include "hardware/potentiometer/Potentiometer.h"
#include "hardware/button/Button.h"
#include "hardware/servomotor/ServoMotor.h"
#include "State.h"
#include "Arduino.h"

MotorControl::MotorControl(int pin_servo, int pin_pot, int pin_button){
    this->pin_button = pin_button;
    this->pin_pot = pin_pot;
    this->pin_servo = pin_servo;
    this->state = OFF;
}

void MotorControl::init(){
    this->potentiometer = new Potentiometer(this->pin_pot);
    this->button = new Button(this->pin_button);
    this->servoMotor = new ServoMotor(this->pin_servo);
}

void MotorControl::manualControl(){
    this->servoMotor->setAngle(this->potentiometer->readValue());
}

void MotorControl::automaticControl(int minWaterLevel, int maxWaterLevel, int waterLevel){
    this->servoMotor->setAngle(map(waterLevel, minWaterLevel, maxWaterLevel, 0, 180));
}

void MotorControl::off(){
    
}
