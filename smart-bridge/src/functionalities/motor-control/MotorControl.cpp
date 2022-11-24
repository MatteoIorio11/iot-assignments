#include "MotorControl.h"
#include "hardware/potentiometer/Potentiometer.h"
#include "hardware/button/Button.h"
#include "hardware/servomotor/ServoMotor.h"
#include "State.h"
#include "Arduino.h"

/// @brief constructor of the motor control
/// @param pin_servo 
/// @param pin_pot 
/// @param pin_button 
MotorControl::MotorControl(int pin_servo, int pin_pot, int pin_button){
    this->pin_button = pin_button;
    this->pin_pot = pin_pot;
    this->pin_servo = pin_servo;
    this->MANUAL_CONTROL_PC = false;
    this->state = AUTOMATIC;
}
/// @brief initializing of the components 
void MotorControl::init(){
    this->potentiometer = new Potentiometer(this->pin_pot);
    this->button = new Button(this->pin_button);
    this->servoMotor = new ServoMotor(this->pin_servo);
    
}
/// @brief set the angle of the servo motor reading the value from the potetiometer
void MotorControl::manualControl(){
    int res = JsonDeserializer::getAngle();
    if(res >= 0){
        this->servoMotor->setAngle(res);
        this->MANUAL_CONTROL_PC=false;
    }else if(res == CODE_SWITCH_CONTROL || this->MANUAL_CONTROL_PC){
        this->MANUAL_CONTROL_PC=true;
        int angle = this->potentiometer->readValue();
        this->servoMotor->setAngle(angle);
    }
}
/// @brief remapping the value
/// @param x 
/// @param in_min 
/// @param in_max 
/// @param out_min 
/// @param out_max 
/// @return the mapped value
int MotorControl::mapF(float x, float in_min, float in_max, float out_min, float out_max) {
    int  result;
    result = (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    return result;
}
/// @brief set the angle of the servo motor by reading the water level input
/// @param minWaterLevel 
/// @param maxWaterLevel 
/// @param waterLevel 
void MotorControl::automaticControl(float minWaterLevel, float maxWaterLevel, float waterLevel){
    int angle = mapF(waterLevel, minWaterLevel, maxWaterLevel, 0, 180);
    this->servoMotor->setAngle(angle);
}
/// @brief setting the state to OFF
void MotorControl::off(){
    this->state = OFF;
}
/// @brief setting the state to AUTOMATIC
void MotorControl::automatic(){
    this->state = AUTOMATIC;
}
/// @brief setting the state to MANUAL
void MotorControl::manual(){
    this->state = MANUAL;
}
/// @brief getter for the button's pin
/// @return the pin of the button 
int MotorControl::getPinButton(){
    return this->pin_button;
}
/// @brief getter for the potentiometer's pin
/// @return the pin of the potentiometer
int MotorControl::getPinPotentiometer(){
    return this->pin_pot;
}
/// @brief getter for the servo motor's pin
/// @return the pin of the servo motor
int MotorControl::getPinServoMotor(){
    return this->pin_servo;
}
/// @brief getter for the potentiometer
/// @return  the value of the potentiometer
Potentiometer MotorControl::getPotentiometer(){
    return *this->potentiometer;
}
/// @brief getter for the servo motor
/// @return  the value of the servo motor
ServoMotor MotorControl::getServoMotor(){
    return *this->servoMotor;
}
/// @brief getter for the button
/// @return the value of the button
Button MotorControl::getButton(){
    return *this->button;
}
/// @brief getter for the actual state
/// @return the actual state of the motor control
MotorState MotorControl::getState(){
    return this->state;
}
/// @brief set the angle of the servo motor to 0
void MotorControl::closeValve(){
    this->servoMotor->setAngle(0);
}
