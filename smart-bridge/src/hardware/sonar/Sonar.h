#ifndef __SONAR__
#define __SONAR__

#include "hardware/component/Component.h"

class Sonar{
    private:
        const double VS =  331.45 + 0.62*20;
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