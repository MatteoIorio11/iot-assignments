#include "functionalities/motor-control/MotorControl.h"
#include "LogicMC.h"

MotorControl* mc;

void initMC(int pin_servo, int pin_pot, int pin_button){
    mc = new MotorControl(int pin_servo, int pin_pot, int pin_button);
}

void tickMC(){
    switch (mc->getState())
    {
        case OFF:
            break;
        case AUTOMATIC:
            break;
        case MANUAL:
            break;
    }
}