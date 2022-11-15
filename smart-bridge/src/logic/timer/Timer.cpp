#include "Timer.h"

TimerOne* timer;
volatile TimerState state = STOP;

void changeState(){
    state = state == STOP ? GO : STOP;
}

void initTimer(int period, TimerOne* timer){
    timer = timer;
    timer->initialize(NORMAL_STATE_SAMPLING);
    timer->attachInterrupt(changeState);
}

void waitForTheNextTick(){
    while(state == STOP){}
    state = GO;
}

void changePeriod(WaterState state){
    timer->detachInterrupt();
    switch (state)
    {
        case NORMAL: 
            timer->initialize(NORMAL_STATE_SAMPLING);
            break;
        case PRE_ALARM:
            timer->initialize(PREALARM_STATE_SAMPLING);
            break;
        case ALARM:
            timer->initialize(ALARM_STATE_SAMPLING); 
            break;
    }
    timer->attachInterrupt(changeState);
}

