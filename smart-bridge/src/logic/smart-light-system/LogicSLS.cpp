#include <TimerOne.h>
#include <EnableInterrupt.h>
#include "LogicSLS.h"
#include "SmartLightSystem/SmartLightSystem.h"

#define THREESHOLD_LUMINOSITY 0
#define TIMER_T1 2*pow(10,6)

SmartLightSystem* sls;
bool another_detected = false;
int shutLedCounter = 0;

void shutLedTimer(){
    if(shutLedCounter == 0){
        shutLedCounter++;
    }else{
        shutLedCounter = 0;
        if(!another_detected){
            sls->notDetected();
            Timer1.detachInterrupt();
        }else{
            another_detected = false; // A person is detected.
            personDetected();
        }
    }
}

void shutLed(){
    sls->turnOffLed();
}

void personDetected(){
    another_detected = true;
    sls->detected(); // change the status of the Smart Light System, because a person is detected
    Timer1.detachInterrupt();
    Timer1.initialize(TIMER_T1);
    Timer1.attachInterrupt(shutLedTimer);
}

void initSLS(SmartLightSystem *smartlightsystem){
    sls = smartlightsystem;
    enableInterrupt(sls->getPinPir(), personDetected, HIGH);
    //If the luminosity is too high, I do not have to turn on the led.
    enableInterrupt(sls->getPinPhotoresistor(), shutLed, sls->getPhotoresistor().readValue() >= THREESHOLD_LUMINOSITY);
}

void tick(){
    switch (sls->getState())
    {
        case DETECTED:
            if(sls->getLuminosity() < THREESHOLD_LUMINOSITY){
                sls->turnOnLed();
            }else{
                sls->turnOffLed();
            }
            break;
        case NOT_DETECTED:
            break;
        case ALERT:
            sls->turnOffLed();
            break;
        
        default:
            break;
    }
}

