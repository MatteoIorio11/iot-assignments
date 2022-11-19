#ifndef __WATERFLOWCONTROLSYSTEM__
#define __WATERFLOWCONTROLSYSTEM__

#include "hardware/sonar/Sonar.h"
#include "hardware/led/GreenLed.h"
#include "hardware/led/RedLed.h"
#include "hardware/lcd/MonitorLcd.h"
#include "logic/timer/Timer.h"
#include "State.h"

#define MINIMUM_SONAR_DISTANCE (float)0.001
#define WL2_BOUND (float)0.3
#define WL1_BOUND (float)0.9
#define MAXIMUM_SONAR_DISTANCE (float)1.00

class WaterflowControlSystem{
    private:
        float last_level_detected;
        int sonar_echoPin;
        int sonar_trigPin;
        int red_pin_led;
        int green_pin_led;
        int address;
        int rows;
        int cols;
        GreenLed* greenLed;
        RedLed* redLed;
        WaterState state;
        MonitorLcd* lcd;
        Sonar* sonar;

    public:
        WaterflowControlSystem(int sonar_echoPin, int sonar_trigPin, int red_pin_led, int green_pin_led, int address, int rows, int cols);
        void init();
        //Led
        void turnOnRedLed();
        void turnOffRedLed();
        void turnOnGreenLed();
        void turnOffGreenLed();
        void RedLedBlink();
        //State
        void updateState(WaterState state);
        float getWaterLevel();
        void refreshWaterState(Timer* timer);
        //Lcd
        void displaySetUp();
        void displayPreAlarm(double level);
        void displayAlarm(double level, int op_degree);
        void turnOnDisplay();
        void turnOffDisplay();
        //Getters
        WaterState getState();
        Sonar getSonar();
        RedLed getRedLed();
        GreenLed getGreenLed();
        MonitorLcd getLcd();
        int getSonarEchoPin();
        int getSonarTrigPin();
        int getRedLedPin();
        int getGreenLedPin();
        float getLastLevelDetected();
        
        void behaveAsNormal();
        void behaveAsPreAlaram(Timer* timer);
        void behaveAsAlarm(Timer* timer);
        
        
};


#endif