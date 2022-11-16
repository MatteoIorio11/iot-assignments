#ifndef __ BRIDGE__
#define __BRIDGE__

#include "logic/logic-smart-light-system/LogicSLS.h"
#include "logic/logic-water-control-system/LogicWCS.h"
#include "logic/timer/Timer.h"
#include "task/Task.h"
// PINS OF THE HARDWARE 
#define PIN_LED_SLS 12
#define PIN_GREENLED_WCS 11
#define PIN_REDLED_WCS 10
#define PIN_SONAR 9
#define PIN_SONAR_TRG 8
#define PIN_POTENTIOMETER 7
#define PIN_BUTTON 6
#define PIN_MONITORLCD
#define PIN_PIR 2
#define PIN_PHOTORESISTOR A0
#define PIN_SERVO_MOTOR A1
#define PERIOD 100
class Bridge : public Task{
    private:
        Timer *timer;
    public:
        Bridge();
        void init();
        void tick();
        Timer* getTimer();
};

#endif