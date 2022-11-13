#include "WaterflowContolSystem.h"
#include "hardware/sonar/Sonar.h"
#include "hardware/led/GreenLed.h"
#include "hardware/led/RedLed.h"
#include "Arduino.h"


WaterflowControlSystem::WaterflowControlSystem(int sonar_echoPin, int sonar_trigPin, int red_pin_led, int green_pin_led){
    this->sonar_echoPin = sonar_echoPin;
    this->sonar_trigPin = sonar_trigPin;
    this->red_pin_led = red_pin_led;
    this->green_pin_led = green_pin_led;
    this->state = NORMAL;
}

void WaterflowControlSystem::init(){
    this->sonar = new Sonar(this->sonar_echoPin, this->sonar_trigPin);
    this->greenLed = new GreenLed(this->green_pin_led);
    this->redLed = new RedLed(this->red_pin_led); 
}

void WaterflowControlSystem::turnOnGreenLed(){
    this->greenLed->ledOn();
}

void WaterflowControlSystem::turnOffGreenLed(){
    this->greenLed->ledOff();
}

void WaterflowControlSystem::turnOnRedLed(){
    this->redLed->ledOn();
}

void WaterflowControlSystem::turnOffRedLed(){
    this->redLed->ledOff();
}

void WaterflowControlSystem::refreshWaterState(){
    //TODO
}

double WaterflowControlSystem::getWaterLevel(){
    //TODO
}

WaterState WaterflowControlSystem::getState(){
    return this->state;
}

Sonar* WaterflowControlSystem::getSonar(){
    return this->sonar;
}

RedLed* WaterflowControlSystem::getRedLed(){
    return this->redLed;
}

GreenLed* WaterflowControlSystem::getGreenLed(){
    return this->greenLed;
}

int WaterflowControlSystem::getSonarEchoPin(){
    this->sonar->getEchoPin();
}

int WaterflowControlSystem::getSonarTrigPin(){
    this->sonar->getTrigPin();
}

int WaterflowControlSystem::getRedLedPin(){
    this->redLed->getPin();
}

int WaterflowControlSystem::getGreenLedPin(){
    this->greenLed->getPin();
}

