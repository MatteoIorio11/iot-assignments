#include "functionalities/motor-control/MotorControl.h"
#include "LogicMC.h"

MotorControl* mc;

void initMC(){
    mc = new MotorControl(int pin_servo, int pin_pot, int pin_button);
}

void tickMC(){
    switch (mc->getState())
    {
    case ON:
        break;
    
    default:
        break;
    }
}