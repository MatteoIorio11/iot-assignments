#include "WaterflowContolSystem.h"
#include "hardware/sonar/Sonar.h"
#include "Arduino.h"


WaterflowControlSystem::WaterflowControlSystem(int echoPin, int trigPin){
    this->echoPin = echoPin;
    this->trigPin = trigPin;
    this->WarningLevels = NORMAL;
}

void WaterflowControlSystem::init(){
    this->sonar = new Sonar(this->echoPin, this->trigPin);
}

void WaterflowControlSystem::tick(){
    this->detectWarningState();
    switch (this->WarningLevels)
    {
    case NORMAL:
        break;
    case WL1:
        break;
    case WL2:
        break;
    }
}

void WaterflowControlSystem::detectWarningState(){
    //this->WarningLevels = this->sonar->getDistance 
}
