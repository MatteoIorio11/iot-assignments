#include "functionalities/motor-control/MotorControl.h"
#include "functionalities/waterflow-control-system/WaterflowContolSystem.h"
#include "LogicWCS.h"
#include <EnableInterrupt.h>

MotorControl* mc;
WaterflowControlSystem* wcs;

void buttonHandler(){
    switch(mc->getState())
    {
        case AUTOMATIC:
            mc->manual();
            break;
        case MANUAL:
            mc->automatic();
            break;
    }
}

void initWCS(int pin_servo, int pin_pot, int pin_button){
    mc = new MotorControl(pin_servo, pin_pot, pin_button);
    enableInterrupt(mc->getButton().getPin(), buttonHandler, RISING);
}

void automatic(){
    mc->automatic();
}

void tickWCS(){
    switch (wcs->getState())
    {
        case NORMAL:
            break;
        case PRE_ALARM:
            break;
        case ALARM:
            switch (mc->getState())
            {
                case OFF:
                    mc->closeValve();
                    break;
                case AUTOMATIC:
                    
                    break;
                case MANUAL:
                    mc->manualControl();
                    break;
            
            }
            break;
    }
}