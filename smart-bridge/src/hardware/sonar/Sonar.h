#ifndef __SONAR__
#define __SONAR__

#include "hardware/component/Component.h"

#define VS 33 + 0.6*20;

class Sonar : public Component{
    private: 
        int trigPin;
        int pin;
        void sendImpulse();
    public:
        Sonar(int trigPin, int echoPin);
        int readValue();
        int getEchoPin();
        int getTrigPin();
};

#endif