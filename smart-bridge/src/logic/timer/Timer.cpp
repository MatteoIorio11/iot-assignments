#include "Timer.h"

Timer::Timer(int period){
    this->timer = new TimerOne();
    this->timer->initialize(NORMAL_STATE_SAMPLING);
}

void Timer::changePeriod(WaterState state){
    this->timer->detachInterrupt();
    switch (state)
    {
        case NORMAL:
        /* code */
            break;
    
        default:
            break;
    }
    this->timer->initialize();
}

