#ifndef __MYTIMER__
#define __MYTIMER__

#include "TimerState.h"
#include <Arduino.h>
#include "constants/Constants.h"

class Timer{
    private:
        hw_timer_t *timer;
        portMUX_TYPE timerMux;
        volatile TimerState state;
    public:
        Timer();
        void waitForTheNextTick();
        void changeState();
        hw_timer_t* getTimer();
        TimerState getState();
};

#endif