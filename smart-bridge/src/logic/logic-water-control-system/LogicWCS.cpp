#include "functionalities/motor-control/MotorControl.h"
#include "functionalities/waterflow-control-system/WaterflowContolSystem.h"
#include "LogicWCS.h"
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

void initWCS(int pin_servo, int pin_pot, int pin_button, int sonar_echoPin, int sonar_trigPin, int red_pin_led, int green_pin_led, int address, int rows, int cols){
    mc = new MotorControl(pin_servo, pin_pot, pin_button);
    wcs = new WaterflowControlSystem(sonar_echoPin, sonar_trigPin, red_pin_led, green_pin_led, address, rows, cols);
    enableInterrupt(mc->getButton().getPin(), buttonHandler, RISING);
}

void automatic(){
    mc->automatic();
}

void tickWCS(){
    switch (wcs->getState())
    {
        case NORMAL:
            wcs->turnOnGreenLed();
            wcs->turnOffRedLed();
            wcs->turnOffDisplay();
            mc->automatic();
            break;
        case PRE_ALARM:
            wcs->turnOnDisplay();
            wcs->turnOffGreenLed();
            wcs->RedLedBlink();
            wcs->displayPreAlarm(wcs->getWaterLevel());
            break;
        case ALARM:
            wcs->turnOnDisplay();
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
            //wcs->displayAlarm(wcs->getWaterLevel(), ) Need potentiometer alpha
            wcs->turnOffGreenLed();
            wcs->turnOnRedLed();
            break;
    }
}