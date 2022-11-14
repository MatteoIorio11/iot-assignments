#ifndef __TIMETICK__
#define __TIMERTICK__

#include <TimerOne.h>
#include "functionalities/waterflow-control-system/State.h"
#include "State.h"

#define NORMAL_STATE_SAMPLING pow(10, 4)
#define PREALARM_STATE_SAMPLING pow(10, 4)/2
#define ALARM_STATE_SAMPLING pow(10, 4)/4


class Timer{
    private:
        TimerOne* timer;
        TimerState state;
        void waitForTheNextTick();
    public:
        Timer(int period);
        void changePeriod(WaterState state);

};

#endif