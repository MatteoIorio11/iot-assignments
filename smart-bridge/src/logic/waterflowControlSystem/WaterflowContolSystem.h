#ifndef __WATERFLOWCONTROLSYSTEM__
#define __WATERFLOWCONTROLSYSTEM__

#include "sonar/Sonar.h"



class WaterflowControlSystem{
    private:
        int echoPin;
        int trigPin;
        enum  { NORMAL, WL1, WL2} WarningLevels;
        Sonar* sonar;
    public:
        WaterflowControlSystem(int echoPin, int trigPin);
        void init();
        void tick();
        void detectWarningState();
};


#endif