#include "functionalities/smart-light-system/SmartLightSystem.h"
#include "LogicSLS.h"
#include "Arduino.h"
#include "contants/Constants.h"
//The bound where we can decide if the led is On or Off


SmartLightSystem* sls;  //The smart light system
int timer_tick = 0;     //Timer for the light 
long period = 0;        //Period used inside the main's timer

void initSLS(int pin_pir, int pin_led, int pin_photo, int per){
    sls = new SmartLightSystem(pin_pir, pin_led, pin_photo);
    sls->init();    //Init of the components inside the system
    period = per;   //Setting the period
}

void setAlarm(){
    //Setting the alarm. This method is called by TickWCS when It switched in ALARM state
    sls->alarm();
    sls->turnOffLed();
}

bool isInAlarmState(){
    return sls->getState() == SLS_ALARM;// Check if the system is in the alarm state 
}

void resetStatus(){
    // This method will be called inside the TickWCS for example when we pass from the ALARM state in another state. But the previous state must be ALARM 
    sls->notDetected();             // Changing the state of the bridge in NOT_DETECTED. 
}

void checkForLuminosity(){
    if(sls->getLuminosity() >= 0 and sls->getLuminosity() < LUMINOSITY_LOWERBOUND){
        //There is no much light, so the led must be on
        sls->turnOnLed();            // Turning ON the led
    }else{
        sls->turnOffLed();           // Turning OFF the led
    }
}

void tickSLS(float p){
    period = p;                       // Assing the period, because maybe in the Bridge we are in PRE_ALARM or in ALARM 
    switch (sls->getState())
    {
        case DETECTED:
            checkForLuminosity();
            if(timer_tick >= TIMER_T1(period)){
                timer_tick = 0;      // Reset of the Timer
                //The light has to be on only for T1 seconds, in this case the T1 = TIMER_PERIOD
                sls->turnOffLed();   // Turning OFF the led
                sls->notDetected();  // Change the state of the System in NOT_DETECTED
                break;
            }else{
                /*
                Because of the pir sensor, when a person is detected, the pir can send more than one HIGH signals. 
                so in order to resolve this problem, I recognise another person when the signal is HIGH and 
                the signal is sent after SAMPLING_FREQUENCE seconds 
                */
                int SAMPLING_FREQ = TIMER_T1(period)/2;
                if(sls->checkTheBridge() == HIGH and (timer_tick) % SAMPLING_FREQ == 0){
                                    //Another person have been detected, I have to re-initialize the timer_tick
                    timer_tick = 0; // reset of the "timer"
                }
            }
            timer_tick+=1;
            break;
        case NOT_DETECTED:
            if(sls->checkTheBridge() == HIGH){
                //If someone is detected on the bridge we must go in the DETECTED state
                timer_tick = 0;      // Reset the timer
                sls->detected();
            }
            break;
        case SLS_ALARM:
            if(sls->getLed().readValue() == HIGH){
                //If the led was ON we must shut the led because we are in the ALARM state
                sls->turnOffLed();   // Turning OFF the led
                timer_tick = 0;      // reset the timer
            }
            break;
        default:
            break;
    }
}