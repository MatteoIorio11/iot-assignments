#ifndef __MYSERVOMOTOR__
#define __MYSERVOMOTOR__

#include "hardware/component/SimpleComponent.h"
#include "ServoTimer2.h"

#define ZERO_SERVO 550
#define FLAT_ANGLE_SERVO 2300
#define FLAT_ANGLE 180

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