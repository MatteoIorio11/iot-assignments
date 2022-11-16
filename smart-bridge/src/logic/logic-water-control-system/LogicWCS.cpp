#include "functionalities/motor-control/MotorControl.h"
#include "functionalities/waterflow-control-system/WaterflowContolSystem.h"
#include "LogicWCS.h"
#include "logic/logic-smart-light-system/LogicSLS.h"
#include <EnableInterrupt.h>

MotorControl* mc;
WaterflowControlSystem* wcs;
Timer* timer;

void buttonHandler(){
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

void initWCS(Timer* t, int pin_servo, int pin_pot, int pin_button, int sonar_echoPin, int sonar_trigPin, int red_pin_led, int green_pin_led, int address, int rows, int cols){
    timer = t;
    mc = new MotorControl(pin_servo, pin_pot, pin_button);
    wcs = new WaterflowControlSystem(sonar_echoPin, sonar_trigPin, red_pin_led, green_pin_led, address, rows, cols);
    enableInterrupt(mc->getButton().getPin(), buttonHandler, RISING);
}

void automatic(){
    mc->automatic();
}

void tickWCS(){
    wcs->refreshWaterState(timer);
    switch (wcs->getState())
    {
        case NORMAL:
            tickSLS();
            wcs->turnOffDisplay();
            wcs->turnOnGreenLed();
            wcs->turnOffRedLed();
            break;
        case PRE_ALARM:
            tickSLS();
            wcs->turnOffGreenLed();
            wcs->RedLedBlink(); // non spostare
            wcs->turnOnDisplay();
            wcs->displayPreAlarm(wcs->getWaterLevel()); // non spostare
            break;
        case ALARM:
            wcs->turnOffGreenLed();
            wcs->turnOnRedLed();
            wcs->turnOnDisplay();
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
                    mc->automaticControl(WL2_BOUND, MAXIMUM_SONAR_DISTANCE, wcs->getWaterLevel());
                    break;
                case MANUAL:
                    mc->manualControl();
                    break;
            }
            break;
    }
}