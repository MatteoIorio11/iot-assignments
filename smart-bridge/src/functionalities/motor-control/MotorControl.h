#ifndef __MOTORCONTROL__
#define __MOTORCONTROL__



#include "hardware/servomotor/ServoMotor.h"
#include "hardware/potentiometer/Potentiometer.h"
#include "hardware/button/Button.h"
#include "functionalities/json/json-deserialization/JsonDeserializer.h"
#include "State.h"
 

class MotorControl{
    private:
        bool MANUAL_CONTROL_PC;
        int pin_servo;
        int pin_pot;
        int pin_button;
        ServoMotor* servoMotor;
        Potentiometer* potentiometer;
        Button* button;
        MotorState state;
        int mapF(float x, float in_min, float in_max, float out_min, float out_max);
        
    public:
        MotorControl(int pin_servo, int pin_pot, int pin_button);
        void init();
        void manualControl();
        void automaticControl(float minWaterLevel, float maxWaterLevel, float waterLevel);
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