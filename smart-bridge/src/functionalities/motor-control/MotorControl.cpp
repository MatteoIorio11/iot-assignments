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
    this->MANUAL_CONTROL_PC = false;
    this->state = AUTOMATIC;
}

void MotorControl::init(){
    this->potentiometer = new Potentiometer(this->pin_pot);
    this->button = new Button(this->pin_button);
    this->servoMotor = new ServoMotor(this->pin_servo);
    
}

void MotorControl::buttonHandler(){

}

void MotorControl::manualControl(){
    int angle = this->potentiometer->readValue();
    if(!Serial.available() && !this->MANUAL_CONTROL_PC){
        this->servoMotor->setAngle(angle);
    }else{
        angle = JsonDeserializer::getAngle();
        if(angle != -1){
            this->servoMotor->setAngle(angle);
        }
    }
}

int MotorControl::mapF(float x, float in_min, float in_max, float out_min, float out_max) {
    int  result;
    result = (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    return result;
}

void MotorControl::automaticControl(float minWaterLevel, float maxWaterLevel, float waterLevel){
    int angle = mapF(waterLevel, minWaterLevel, maxWaterLevel, 0, 180);
    this->servoMotor->setAngle(angle);
}

void MotorControl::off(){
    this->state = OFF;
}

void MotorControl::automatic(){
    this->state = AUTOMATIC;
}

void MotorControl::manual(){
    this->state = MANUAL;
}

int MotorControl::getPinButton(){
    return this->pin_button;
}

int MotorControl::getPinPotentiometer(){
    return this->pin_pot;
}

int MotorControl::getPinServoMotor(){
    return this->pin_servo;
}

Potentiometer MotorControl::getPotentiometer(){
    return *this->potentiometer;
}

ServoMotor MotorControl::getServoMotor(){
    return *this->servoMotor;
}

Button MotorControl::getButton(){
    return *this->button;
}

MotorState MotorControl::getState(){
    return this->state;
}

void MotorControl::closeValve(){
    this->servoMotor->setAngle(0);
}
