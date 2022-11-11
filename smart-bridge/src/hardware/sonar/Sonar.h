#ifndef __SONAR__
#define __SONAR__

#include "hardware/component/Component.h";

#define VS 331.5 + 0.6*20;

class Sonar : public Component{
    private: 
        int trigPin;
        int pin;
        void sendImpulse();
    public:
        Sonar(int trigPin, int echoPin);
        int readValue();
};

#endif