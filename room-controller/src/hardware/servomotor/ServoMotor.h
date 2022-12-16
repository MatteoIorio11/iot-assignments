#ifndef __MYSERVOMOTOR__
#define __MYSERVOMOTOR__

#include "hardware/hardware/SimpleHardware.h"
#include "ServoTimer2.h"
#include "constants/Constants.h"


class ServoMotor: public SimpleHardware{
    private:
        int pin;
        int percentage;
        ServoTimer2* servoMotor;
    public:
        ServoMotor(int pin);
        void setOpening(int percentage);
        void close();
        void open();
        int getOpening();
};

#endif