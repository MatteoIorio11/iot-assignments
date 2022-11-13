#include "functionalities/motor-control/MotorControl.h"
#include "functionalities/waterflow-control-system/WaterflowContolSystem.h"
#include "LogicWCS.h"

MotorControl* mc;
WaterflowControlSystem* wcs;
void initWCS(int pin_servo, int pin_pot, int pin_button){
    mc = new MotorControl(pin_servo, pin_pot, pin_button);
}

void automatic(){
    mc->automatic();
}

void tickWCS(){
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