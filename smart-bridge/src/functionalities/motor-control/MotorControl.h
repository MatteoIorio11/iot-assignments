#ifndef __MOTORCONTROL__
#define __MOTORCONTROL__



#include "hardware/servomotor/ServoMotor.h"
#include "hardware/potentiometer/Potentiometer.h"
#include "hardware/button/Button.h"

class MotorControl{
    private:
        int pin_servo;
        int pin_pot;
        int pin_button;
        ServoMotor* servoMotor;
        Potentiometer* potentiometer;
        Button* button;
        
    public:
        MotorControl(int pin_servo, int pin_pot, int pin_button);
        void init();
        void manualControl();
        void automaticControl();
        //State
        void Off();
        void On();
        void Automatic();
        void Manual();
        //Getters
        int getPinServoMotor();
        int getPinPotentiometer();
        int getPinButton();
};

#endif