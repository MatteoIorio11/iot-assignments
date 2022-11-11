#ifndef __SMARTLIGHTSYSTEM__
#define __SMARTLIGHTSYSTEM__

#define TIMER_T1 3*pow(10, 6)


#include "task/Task.h"
#include "pir/Pir.h"
#include "led/GreenLed.h"
#include "photoresistor/PhotoResistor.h"
#include "State.h"

class SmartLightSystem{
    private:
        int pin_pir;
        int pin_led;
        int pin_photo;
        Pir* pir;
        GreenLed* greenled;
        PhotoResistor* photoResistor;
        State state;
        
    public:
        SmartLightSystem(int pin_pir, int pin_led, int pin_photo);
        void init();
        State getState();
        void turnOnLed();
        void turnOffLed();
        int getLuminosity();
        void detected();
        void notDetected();
        void checkPerson();
        PhotoResistor getPhotoresistor();
};

#endif