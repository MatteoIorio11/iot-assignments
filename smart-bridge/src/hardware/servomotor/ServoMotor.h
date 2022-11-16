#ifndef __MYSERVOMOTOR__
#define __MYSERVOMOTOR__

#include "hardware/component/SimpleComponent.h"
#include "ServoTimer2.h"

class ServoMotor: public SimpleComponent{
    private:
        int pin;
        int angle;
        ServoTimer2* servoMotor;
    public:
        ServoMotor(int pin);
        void setAngle(int angle);
        int getAngle();
};

#endif