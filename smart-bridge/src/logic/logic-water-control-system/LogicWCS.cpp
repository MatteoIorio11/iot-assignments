#include "functionalities/motor-control/MotorControl.h"
#include "functionalities/waterflow-control-system/WaterflowContolSystem.h"
#include "LogicWCS.h"
#include "logic/logic-smart-light-system/LogicSLS.h"
#include <EnableInterrupt.h>

MotorControl* mc;
WaterflowControlSystem* wcs;

void buttonHandler(){
    switch(mc->getState())
    {
        case OFF:
            break;
        case AUTOMATIC:
            mc->manual();
            break;
        case MANUAL:
            mc->automatic();
            break;
    }
}

void refreshWaterState(){
    WaterState tmpState;
    if(wcs->getWaterLevel() > MINIMUM_SONAR_DISTANCE && wcs->getWaterLevel() <= WL1_BOUND){
        tmpState = NORMAL;
    }else if(wcs->getWaterLevel() > WL1_BOUND && wcs->getWaterLevel() <= WL2_BOUND){
        tmpState = PRE_ALARM;

    }else if(wcs->getWaterLevel() > WL2_BOUND){
        tmpState = ALARM;
    }
    if(wcs->getState() != tmpState){
        wcs->updateState(tmpState);
    }
}

void initWCS(int pin_servo, int pin_pot, int pin_button, int sonar_echoPin, int sonar_trigPin, int red_pin_led, int green_pin_led, int address, int rows, int cols){
    mc = new MotorControl(pin_servo, pin_pot, pin_button);
    wcs = new WaterflowControlSystem(sonar_echoPin, sonar_trigPin, red_pin_led, green_pin_led, address, rows, cols);
    enableInterrupt(mc->getButton().getPin(), buttonHandler, RISING);
}

void automatic(){
    mc->automatic();
}

void tickWCS(){
    refreshWaterState();
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
            wcs->RedLedBlink();
            wcs->turnOnDisplay();
            wcs->displayPreAlarm(wcs->getWaterLevel());
            break;
        case ALARM:
            wcs->turnOffGreenLed();
            wcs->turnOffRedLed();
            wcs->turnOnDisplay();
            wcs->displayAlarm(wcs->getWaterLevel(), mc->getServoMotor().getAngle()); 
            if(!isInAlarmState()){
                //If the Smart light system is not in the alarm state It must be setted
                setAlarm();
            }
            switch (mc->getState())
            {
                case OFF:
                    mc->closeValve();
                    break;
                case AUTOMATIC:
                    //mc->automaticControl(min,max,mc->getButton().getPin());
                    break;
                case MANUAL:
                    mc->manualControl();
                    break;
            }
            break;
    }
}