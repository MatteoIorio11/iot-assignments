#ifndef __SMARTLIGHTSYSTEM__
#define __SMARTLIGHTSYSTEM__

#define TIMER_T1 3*pow(10, 6)


#include "task/Task.h"
#include "pir/Pir.h"
#include "led/GreenLed.h"

class SmartLightSystem : public Task{
    private:
        int pin_pir;
        int pin_led;
        Pir* pir;
        GreenLed* greenled;
        enum {DETECTED, NOT_DETECTED, ALERT} state;
        
    public:
        SmartLightSystem(int pin_pir, int pin_led);
        void init();
        void tick();
        void checkPerson();
};

#endif