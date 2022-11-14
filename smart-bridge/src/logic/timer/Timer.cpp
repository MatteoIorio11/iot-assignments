#include "Timer.h"

TimerOne* timer;
TimerState state;


void initTimer(int period){
    timer = new TimerOne();
    timer->initialize(NORMAL_STATE_SAMPLING);
    timer->attachInterrupt(NULL);
    
}


void changePeriod(WaterState state){
    timer->detachInterrupt();
    switch (state)
    {
        case NORMAL:
        /* code */
            break;
    
        default:
            break;
    }
    timer->initialize();
}

