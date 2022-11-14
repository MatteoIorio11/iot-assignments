#ifndef __MOTORCONTROL__
#define __MOTORCONTROL__



#include "hardware/servomotor/ServoMotor.h"
#include "hardware/potentiometer/Potentiometer.h"
#include "hardware/button/Button.h"
#include "State.h"

class MotorControl{
    private:
        int pin_servo;
        int pin_pot;
        int pin_button;
        ServoMotor* servoMotor;
        Potentiometer* potentiometer;
        Button* button;
        MotorState state;
        
    public:
        MotorControl(int pin_servo, int pin_pot, int pin_button);
        void init();
        void manualControl();
        void automaticControl(int minWaterLevel, int maxWaterLevel, int waterLevel);
        //State
        void off();
        void automatic();
        void manual();
        //Getters
        int getPinServoMotor();
        int getPinPotentiometer();
        int getPinButton();
        MotorState getState();
        Potentiometer getPotentiometer();
        Button getButton();
        ServoMotor getServoMotor();
        void closeValve();
};

#endif