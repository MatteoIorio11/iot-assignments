#include <TimerOne.h>
#include <EnableInterrupt.h>
#include "smart-light-system/SmartLightSystem.h"
#include "LogicSLS.h"

#define THREESHOLD_LUMINOSITY 1.5
//#define TIMER_T1 10*pow(10,6)
#define TIMER_TICK 100
#define TIME_FOR_DETECTION pow(10, 3)
#define TIMER_PERIOD 100
#define SAMPLING_FREQUENCE 50

//If timer t1 == 5 secondi, I can have a sampling of the light inside the shut let timer. For instance, I can set the timer
//to 1 sec and every second I check the light and decide if the led must be on or off

SmartLightSystem* sls;
int timer_tick = 0;

/*
void shutLedTimer(){
    if(shutLedCounter == 0){
        shutLedCounter++;
    }else{
        Serial.println("Timer T1 ends. No one has been detected");
        shutLedCounter = 0;
        sls->notDetected();
        sls->turnOffLed();
        Timer1.detachInterrupt();
    }
}
*/
void initSLS(int pin_pir, int pin_led, int pin_photo){
    sls = new SmartLightSystem(pin_pir, pin_led, pin_photo);
    sls->init();
}

void setAlert(){
    sls->alert();
}

void resetStatus(){
    sls->notDetected();
}

/*
void setTimerT1(){
    Timer1.detachInterrupt();
    Timer1.initialize(TIMER_T1);
    Timer1.attachInterrupt(shutLedTimer);
}
*/

void checkForLuminosity(){
    if(sls->getLuminosity() >= THREESHOLD_LUMINOSITY){
        sls->turnOffLed();
    }else{
        sls->turnOnLed();
    }
}

void tickSLS(){
    switch (sls->getState())
    {
        case DETECTED:
            checkForLuminosity();
            if(timer_tick == TIMER_PERIOD){
                timer_tick = 0;
                sls->notDetected();
                break;
            }else{
                if(sls->checkTheBridge() == HIGH and (timer_tick) % SAMPLING_FREQUENCE == 0){
                    //Another person have been detected, I have to re-initialize the timer T1.
                    Serial.println("Another person has been detected");
                    timer_tick = 0; // reset of the timer
                    //setTimerT1();
                }
            }
            timer_tick+=1;
            break;
        case NOT_DETECTED:
            sls->turnOffLed();
            if(sls->checkTheBridge() == HIGH){
                timer_tick = 0;
                Serial.println("A person has been detected");
                sls->detected();
                //setTimerT1();
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

