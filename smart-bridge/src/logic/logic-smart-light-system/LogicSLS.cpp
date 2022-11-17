#include "functionalities/smart-light-system/SmartLightSystem.h"
#include "LogicSLS.h"
#include "Arduino.h"

#define LUMINOSITY_LOWERBOUND 1
//tick of the timer inside the main, this value is used for the "timer_tick".
#define TIMER_PERIOD period
//The timer1 is ten seconds based on the period
#define TIMER_T1_A(p) ((int)pow(10,7)/p)
#define SAMPLING_FREQUENCE(p) ((int)p/4)
#define MY_TIME pow(10,7)
#define MY_SAMPLING 50

SmartLightSystem* sls; //The smart light system
int timer_tick = 0;    //Timer for the light 
long period = 0;        //Period used inside the main's timer



void initSLS(int pin_pir, int pin_led, int pin_photo, int per){
    sls = new SmartLightSystem(pin_pir, pin_led, pin_photo);
    sls->init();
    period = per;
}

void setAlarm(){
    sls->alarm();
}

bool isInAlarmState(){
    return sls->getState() == ALARM;
}

void changePeriod(int p){
    period = period;
}

void resetStatus(){
    sls->notDetected();
}

void checkForLuminosity(){
    if(sls->getLuminosity() >= 0 and sls->getLuminosity() < LUMINOSITY_LOWERBOUND){
        //There is no much light, so the led must be on
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
            if(timer_tick >= TIMER_T1_A(period)){
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
                if(sls->checkTheBridge() == HIGH and (timer_tick) % MY_SAMPLING == 0){
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
        case ALARM:
            
            if(sls->getLed().readValue() == HIGH){
                sls->turnOffLed();
                timer_tick = 0;
            }
            break;
        
        default:
            break;
    }
}