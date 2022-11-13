#ifndef __SERVOMOTOR__
#define __SERVOMOTOR__

#include "hardware/component/SimpleComponent.h"
#include <Servo.h>

class ServoMotor: public SimpleComponent{
    private:
        int pin;
        int angle;
        Servo servoMotor;
    public:
        ServoMotor(int pin);
        void setAngle(int angle);
        int getAngle();
};

#endif