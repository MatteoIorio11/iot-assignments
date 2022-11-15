#ifndef __ BRIDGE__
#define __BRIDGE__

#include "logic/logic-smart-light-system/LogicSLS.h"
#include "logic/logic-water-control-system/LogicWCS.h"
#include "logic/timer/Timer.h"
#include "task/Task.h"
// PINS OF THE HARDWARE 
#define PIN_LED 12
#define PIN_PIR 2
#define PIN_PHOTORESISTOR A0
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