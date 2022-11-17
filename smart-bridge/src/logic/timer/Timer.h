#ifndef __MYTIMER__
#define __MYTIMER__

#include <TimerOne.h>
#include "functionalities/waterflow-control-system/State.h"
#include "State.h"

#define NORMAL_STATE_SAMPLING pow(10, 3)
#define PREALARM_STATE_SAMPLING pow(10, 3)/2
#define ALARM_STATE_SAMPLING pow(10, 3)/4

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