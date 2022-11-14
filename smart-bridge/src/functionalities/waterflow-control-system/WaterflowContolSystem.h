#ifndef __WATERFLOWCONTROLSYSTEM__
#define __WATERFLOWCONTROLSYSTEM__

#include "hardware/sonar/Sonar.h"
#include "hardware/led/GreenLed.h"
#include "hardware/led/RedLed.h"
#include "State.h"

class WaterflowControlSystem{
    private:
        int sonar_echoPin;
        int sonar_trigPin;
        int red_pin_led;
        int green_pin_led;
        GreenLed* greenLed;
        RedLed* redLed;
        WaterState state;
        Sonar* sonar;
        
    public:
        WaterflowControlSystem(int sonar_echoPin, int sonar_trigPin, int red_pin_led, int green_pin_led);
        void init();
        //Led
        void turnOnRedLed();
        void turnOffRedLed();
        void turnOnGreenLed();
        void turnOffGreenLed();
        //State
        void refreshWaterState();
        double getWaterLevel();
        //Getters
        WaterState getState();
        Sonar getSonar();
        RedLed getRedLed();
        GreenLed getGreenLed();
        int getSonarEchoPin();
        int getSonarTrigPin();
        int getRedLedPin();
        int getGreenLedPin();
        
        
};


#endif