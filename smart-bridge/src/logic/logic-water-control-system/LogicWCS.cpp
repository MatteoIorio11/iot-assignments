#include "functionalities/motor-control/MotorControl.h"
#include "functionalities/waterflow-control-system/WaterflowContolSystem.h"
#include "LogicWCS.h"
#include "logic/logic-smart-light-system/LogicSLS.h"
#include <EnableInterrupt.h>

#define BLINK_2SEC(p) ((pow(10,6))/(p))

MotorControl* mc;
WaterflowControlSystem* wcs;
Timer* timer;
int timer_blinking = 0;

void buttonHandler(){
    static unsigned long last_interrupt_time = 0;
     unsigned long interrupt_time = millis();
  // If interrupts come faster than 200ms, assume it's a bounce and ignore
    if (interrupt_time - last_interrupt_time > 200) 
    {
        switch(mc->getState())
        {
            case OFF:
                break;
            case AUTOMATIC:
                mc->manual();
                break;
            case MANUAL:
                mc->off();
                break;
        }
    }
}


void initWCS(Timer* t, int pin_servo, int pin_pot, int pin_button, int sonar_echoPin, int sonar_trigPin, int red_pin_led, int green_pin_led, int address, int rows, int cols){
    timer = t;
    mc = new MotorControl(pin_servo, pin_pot, pin_button);
    wcs = new WaterflowControlSystem(sonar_echoPin, sonar_trigPin, red_pin_led, green_pin_led, address, rows, cols);
    mc->init();
    wcs->init();
    enableInterrupt(mc->getButton().getPin(), buttonHandler, RISING);
    //wcs->behaveAsAlarm(timer);
    //wcs->behaveAsNormal();
    wcs->behaveAsPreAlaram(timer);
}

void automatic(){
    mc->automatic();
}

void tickWCS(){
    wcs->refreshWaterState(timer);
    //wcs->updateState(PRE_ALARM);
    //wcs->behaveAsNormal();
    //wcs->displayPreAlarm(100);
    switch (wcs->getState())
    {
        case SHUT:
            break;
        case NORMAL:
            //tickSLS(NORMAL_STATE_SAMPLING);
            break;
        case PRE_ALARM:
            tickSLS(PREALARM_STATE_SAMPLING);
            //Serial.println(timer_blinking);
            //Serial.println(BLINK_2SEC(PREALARM_STATE_SAMPLING));
            if(timer_blinking >= BLINK_2SEC(PREALARM_STATE_SAMPLING)){
                wcs->RedLedBlink();
                timer_blinking = 0;
            }else{
                timer_blinking++;
            }
           // wcs->RedLedBlink(); 
            wcs->displayPreAlarm(wcs->getWaterLevel()); // non spostare
            break;
        case ALARM:
            wcs->displayAlarm(wcs->getWaterLevel(), mc->getServoMotor().getAngle()); // non spostare 
            if(!isInAlarmState()){
                //If the Smart light system is not in the alarm state It must be setted
                setAlarm();
            }
            switch (mc->getState())
            {
                case OFF:
                    mc->closeValve();
                    wcs->refreshWaterState(timer);
                    if(wcs->getState() == ALARM){
                        mc->automatic();
                    }
                    break;
                case AUTOMATIC:
                    mc->automaticControl(MINIMUM_SONAR_DISTANCE, WL2_BOUND, wcs->getWaterLevel());
                    break;
                case MANUAL:
                    mc->manualControl();
                    break;
            }
            break;
    }
}