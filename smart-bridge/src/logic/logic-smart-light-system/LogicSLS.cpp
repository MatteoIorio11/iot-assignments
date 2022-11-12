#include <TimerOne.h>
#include <EnableInterrupt.h>
#include "smart-light-system/SmartLightSystem.h"
#include "LogicSLS.h"

#define LUMINOSITY_LOWERBOUND 1
#define TIMER_TICK 100
#define TIME_FOR_DETECTION pow(10, 3)
//The tick of the timer is 
#define TIMER_PERIOD period
#define SAMPLING_FREQUENCE 50

//If timer t1 == 5 secondi, I can have a sampling of the light inside the shut let timer. For instance, I can set the timer
//to 1 sec and every second I check the light and decide if the led must be on or off

SmartLightSystem* sls;
int timer_tick = 0;
int period = 0;

void initSLS(int pin_pir, int pin_led, int pin_photo, int per){
    sls = new SmartLightSystem(pin_pir, pin_led, pin_photo);
    period = per;
    sls->init();
}

void setAlert(){
    sls->alert();
}

void resetStatus(){
    sls->notDetected();
}

void checkForLuminosity(){
    if(sls->getLuminosity() >= 0 and sls->getLuminosity() < LUMINOSITY_LOWERBOUND){
        //There is not much light, so the led must be on
        sls->turnOnLed();
    }else{
        sls->turnOffLed();
    }
}

void tickSLS(){
    switch (sls->getState())
    {
        case DETECTED:
            checkForLuminosity();
            if(timer_tick >= TIMER_PERIOD){
                timer_tick = 0;
                //The light has to be on only for T1 seconds, in this case the T1 = TIMER_PERIOD
                sls->notDetected();
                break;
            }else{
                /*
                Because of the pir sensor, when a person is detected, the pir can send more than one HIGH signals. 
                so in order to resolve this problem, I recognise another person when the signal is HIGH and 
                the signal is sent after SAMPLING_FREQUENCE seconds 
                */
                if(sls->checkTheBridge() == HIGH and (timer_tick) % SAMPLING_FREQUENCE == 0){
                    //Another person have been detected, I have to re-initialize the timer_tick
                    Serial.println("Another person has been detected");
                    timer_tick = 0; // reset of the "timer"
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
            }
            break;
        case ALERT:
            if(sls->getLed().readValue() == HIGH){
                sls->turnOffLed();
                timer_tick = 0;
            }
            break;
        
        default:
            break;
    }
}

