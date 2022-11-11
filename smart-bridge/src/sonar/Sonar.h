#ifndef __SONAR__
#define __SONAR__

#define VS 331.5 + 0.6*20;

class Sonar{
    private: 
        int trigPin;
        int echoPin;
        void sendImpulse();
    public:
        Sonar(int trigPin, int echoPin);
        int getDistance();
};

#endif