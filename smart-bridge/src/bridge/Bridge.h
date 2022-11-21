#ifndef __BRIDGE__
#define __BRIDGE__

#include "logic/logic-smart-light-system/LogicSLS.h"
#include "logic/logic-water-control-system/LogicWCS.h"
#include "logic/timer/Timer.h"
#include "task/Task.h"
#include "contants/Constants.h"


class Bridge : public Task{
    private:
        Timer *timer;
    public:
        Bridge();
        void init();
        void tick();
        Timer* getTimer();
};

#endif