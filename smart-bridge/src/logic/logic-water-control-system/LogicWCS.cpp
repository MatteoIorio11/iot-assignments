#include "functionalities/motor-control/MotorControl.h"
#include "functionalities/water-flow-state/State.h"
#include "functionalities/waterflow-control-system/WaterflowContolSystem.h"t
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
                    /* code */
                    break;
                case AUTOMATIC:
                    break;
                case MANUAL:
                    break;
            
            }
            break;
    }
}