#ifndef __SONAR__
#define __SONAR__

#include "hardware/component/Component.h"

class Sonar{
    private:
        int trigPin;
        int pin;
        void sendImpulse();
    public:
        Sonar(int trigPin, int echoPin);
        float readValue();
        int getEchoPin();
        int getTrigPin();
};

#endif