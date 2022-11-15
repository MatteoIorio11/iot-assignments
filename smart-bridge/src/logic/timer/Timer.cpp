#include "Timer.h"
#include <avr/sleep.h>

TimerOne* timer;
volatile bool flag;
volatile TimerState state;

void changeState(){
    state = state == STOP ? GO : STOP;
    flag = true;
    //sleep_disable();
}

void initTimer(TimerOne* timer){
    timer = timer;
    flag = false;
    state = STOP;
    timer->initialize(pow(10, 6));
    timer->attachInterrupt(changeState);
}

void waitForTheNextTick(){
    //sleep_enable();
    //sleep_mode();
    while(state == STOP){Serial.println("STOP");}
    state = STOP;
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

