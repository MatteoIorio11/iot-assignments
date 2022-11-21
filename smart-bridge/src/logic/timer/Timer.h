#ifndef __MYTIMER__
#define __MYTIMER__

#include <TimerOne.h>
#include "functionalities/waterflow-control-system/State.h"
#include "State.h"
#include "contants/Constants.h"

class Timer{
    private:
        TimerOne* timer;
        volatile TimerState state;
    public:
        Timer();
        TimerOne* getTimerOne();
        void changePeriod(WaterState waterS);
        void waitForTheNextTick();
        void changeState();
        TimerState getState();
};

#endif