#include "Timer.h"


Timer::Timer(){
    this->timer = new TimerOne();
    this->timer->initialize(NORMAL_STATE_SAMPLING);
    this->state = STOP;
}

TimerOne* Timer::getTimerOne(){
    return this->timer;
}

void Timer::waitForTheNextTick(){
    while(this->state == STOP){}
    this->state = STOP;
}

void Timer::changeState(){
    this->state = this->state == STOP ? GO : STOP;
}

TimerState Timer::getState(){
    return this->state;
}

void Timer::changePeriod(WaterState waterS){
    switch (waterS)
    {
        case NORMAL: 
            this->timer->setPeriod(NORMAL_STATE_SAMPLING);
            break;
        case PRE_ALARM:
            this->timer->setPeriod(PREALARM_STATE_SAMPLING);
            break;
        case ALARM:
            this->timer->setPeriod(ALARM_STATE_SAMPLING); 
            break;
    }
}
