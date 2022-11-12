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
bool not_detected = false;
int shutLedCounter = 0;

void shutLedTimer(){
    if(shutLedCounter == 0){
        shutLedCounter++;
    }else{
        shutLedCounter = 0;
        if(!not_detected){
            sls->notDetected();
            sls->turnOffLed();
            Timer1.detachInterrupt();
        }else{
            not_detected = false; // A person is detected.
            personDetected();
        }
    }
}

void shutLed(){
    Timer1.detachInterrupt();
    sls->turnOffLed();
}

void personDetected(){
    if(sls->getState() != ALERT){
        not_detected = false;
        sls->detected(); // change the status of the Smart Light System, because a person is detected
        if(sls->getLuminosity() < THREESHOLD_LUMINOSITY){
            //If there is not much luminosity the led must be ON
            sls->turnOnLed();
        }
        Timer1.detachInterrupt();
        Timer1.initialize(TIMER_T1);
        Timer1.attachInterrupt(shutLedTimer);
    }
}

void initSLS(SmartLightSystem *smartlightsystem){
    sls = smartlightsystem;
    enableInterrupt(sls->getPinPir(), personDetected, HIGH);
    //If the luminosity is too high, I do not have to turn on the led.
}

void setAlert(){
    sls->alert();
    Timer1.detachInterrupt();
}

void resetStatus(){
    sls->notDetected();
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
            if(sls->getLed().readValue() == HIGH){
                sls->turnOffLed();
            }
            break;
        case ALERT:
            if(!not_detected){
                not_detected = true;
                if(sls->getLed().readValue() == HIGH){
                    sls->turnOffLed();
                }
            }
            break;
        
        default:
            break;
    }
}

