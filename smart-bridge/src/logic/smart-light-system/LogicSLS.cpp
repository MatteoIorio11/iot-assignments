#include <TimerOne.h>
#include <EnableInterrupt.h>
#include "LogicSLS.h"
#include "smartlightsystem/SmartLightSystem.h"

#define THREESHOLD_LUMINOSITY 0
#define TIMER_T1_SAMPLING 1*pow(10,6)
#define TIMER_T1 10

//If timer t1 == 5 secondi, I can have a sampling of the light inside the shut let timer. For instance, I can set the timer
//to 1 sec and every second I check the light and decide if the led must be on or off

SmartLightSystem* sls;
int shutLedCounter = 0;

void shutLedTimer(){
    if(shutLedCounter == 0){
        shutLedCounter++;
    }else{
        shutLedCounter = 0;
        sls->notDetected();
        sls->turnOffLed();
        Timer1.detachInterrupt();
    }
}


void shutLed(){
    Timer1.detachInterrupt();
    sls->turnOffLed();
}

void initSLS(SmartLightSystem *smartlightsystem){
    sls = smartlightsystem;
}

void setAlert(){
    sls->alert();
    Timer1.detachInterrupt();
}

void resetStatus(){
    sls->notDetected();
}

void setTimerT1(){
    Timer1.detachInterrupt();
    Timer1.initialize(TIMER_T1);
    Timer1.attachInterrupt(shutLedTimer);
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
            if(sls->checkTheBridge() == HIGH){
                //Another person have been detected, I have to re-initialize the timer T1.
                setTimerT1();
            }
            break;
        case NOT_DETECTED:
            if(sls->checkTheBridge() == HIGH){
                sls->detected();
                setTimerT1();
            }
            break;
        case ALERT:
            if(sls->getLed().readValue() == HIGH){
                sls->turnOffLed();
            }
            break;
        
        default:
            break;
    }
}

