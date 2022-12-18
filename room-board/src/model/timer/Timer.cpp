#include "Timer.h"


Timer::Timer(){
    this->timerMux = portMUX_INITIALIZER_UNLOCKED;
    this->timer = timerBegin(0, 80, true);
    timerAlarmWrite(this->timer, TIMER_PERIOD, true);
    timerAlarmEnable(this->timer);
    this->state = STOP;
}


void Timer::waitForTheNextTick(){
    while(this->state == STOP){}
    this->state = STOP;
}

hw_timer_t* Timer::getTimer(){
    return this->timer;
}

void Timer::changeState(){
    this->state = this->state == STOP ? GO : STOP;
}

TimerState Timer::getState(){
    return this->state;
}