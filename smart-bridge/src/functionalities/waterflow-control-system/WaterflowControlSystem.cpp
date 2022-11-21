#include "WaterflowContolSystem.h"
#include "hardware/sonar/Sonar.h"
#include "hardware/led/GreenLed.h"
#include "hardware/led/RedLed.h"
#include "Arduino.h"



WaterflowControlSystem::WaterflowControlSystem(int sonar_echoPin, int sonar_trigPin, int red_pin_led, int green_pin_led, int address, int rows, int cols){
    this->sonar_echoPin = sonar_echoPin;
    this->sonar_trigPin = sonar_trigPin;
    this->red_pin_led = red_pin_led;
    this->green_pin_led = green_pin_led;
    this->address = address;
    this->rows = rows;
    this->cols = cols;
    this->last_level_detected = 0.0;
    this->state = SHUT;
}

/// @brief Creates the object inside the system, in this way the user can not change anything in the system
void WaterflowControlSystem::init(){
    this->sonar = new Sonar(this->sonar_trigPin, this->sonar_echoPin);
    this->greenLed = new GreenLed(this->green_pin_led);
    this->redLed = new RedLed(this->red_pin_led); 
    this->lcd = new MonitorLcd(address, rows, cols);
    this->lcd->init();
}

/// @brief Turns on the Green Led 
void WaterflowControlSystem::turnOnGreenLed(){
    this->greenLed->ledOn();
}

/// @brief Turns off the Green Led
void WaterflowControlSystem::turnOffGreenLed(){
    this->greenLed->ledOff();
}

/// @brief Turns on the Red Led
void WaterflowControlSystem::turnOnRedLed(){
    this->redLed->ledOn();
}

/// @brief Turns of the Red Led 
void WaterflowControlSystem::turnOffRedLed(){
    this->redLed->ledOff();
}

/// @brief Makes the Red Led blink
void WaterflowControlSystem::RedLedBlink(){
    this->redLed->blink();
}

/// @brief Setter for the state param
/// @param state the state which we want to set
void WaterflowControlSystem::updateState(WaterState state){
    this->state = state;
}

/// @brief Displays the Alarm statistics on the LCD
/// @param level the current water level
/// @param op_degree the valve angle
void WaterflowControlSystem::displayAlarm(double level, int op_degree){
    this->lcd->displayAlarm(level, op_degree);
}

/// @brief Displays the pre-alarm statistics on the LCD
/// @param level the water Level
void WaterflowControlSystem::displayPreAlarm(double level){
    this->lcd->displayPreAlarm(level);
}

/// @brief Turns on the LCD display
void WaterflowControlSystem::turnOnDisplay(){
    this->lcd->displayON();
}

/// @brief Turns off the LCD Display
void WaterflowControlSystem::turnOffDisplay(){
    this->lcd->displayOFF();
}

/// @brief Getter for the water level
/// @return the water level
float WaterflowControlSystem::getWaterLevel(){
    return this->sonar->readValue(); 
}

/// @brief Getter for the state
/// @return the current state
WaterState WaterflowControlSystem::getState(){
    return this->state;
}

/// @brief Getter for the Sonar object
/// @return the sonar object
Sonar WaterflowControlSystem::getSonar(){
    return *this->sonar;
}

/// @brief Getter for the Red Led object
/// @return The Red Led object
RedLed WaterflowControlSystem::getRedLed(){
    return *this->redLed;
}

/// @brief Getter for the Green Led object
/// @return The Green Led object
GreenLed WaterflowControlSystem::getGreenLed(){
    return *this->greenLed;
}

/// @brief Getter for the sonar Echo Pin
/// @return The sonar echo pin
int WaterflowControlSystem::getSonarEchoPin(){
    return this->sonar->getEchoPin();
}

/// @brief Getter for the sonar trigPin
/// @return the sonar trig pin
int WaterflowControlSystem::getSonarTrigPin(){
    return this->sonar->getTrigPin();
}

/// @brief Getter for the Red Led pin
/// @return the red led pin
int WaterflowControlSystem::getRedLedPin(){
    return this->redLed->getPin();
}

/// @brief Getter for the Green Led pin
/// @return the green led pin
int WaterflowControlSystem::getGreenLedPin(){
    return this->greenLed->getPin();
}

/// @brief Getter for the last water level detected
/// @return the last water level detected
float WaterflowControlSystem::getLastLevelDetected(){
    return this->last_level_detected;
}

/// @brief Refresh the water state by calculating the distance from the water and detecting which state have to be set
/// @param timer the timer which regulates the detection period
void WaterflowControlSystem::refreshWaterState(Timer* timer){
    this->last_level_detected = this->getWaterLevel();
    if(this->last_level_detected <= WL2_BOUND){
        if(this->state != ALARM){
            this->state = ALARM;
            this->turnOffGreenLed();
            this->turnOnRedLed();
            this->turnOnDisplay();
            timer->changePeriod(ALARM);
        }
    }else if(this->last_level_detected > WL2_BOUND && this->last_level_detected <= WL1_BOUND){
        if(this->state != PRE_ALARM){
            this->state = PRE_ALARM;
            this->turnOffGreenLed();
            this->turnOnDisplay();
            timer->changePeriod(PRE_ALARM);
        }
    }else{
        if(this->state != NORMAL){
            this->state = NORMAL;
            this->turnOffDisplay();
            this->turnOnGreenLed();
            this->turnOffRedLed();
            timer->changePeriod(NORMAL);
        }
    }
}

