#ifndef __SMARTLIGHTSYSTEM__
#define __SMARTLIGHTSYSTEM__

#define TIMER_T1 3*pow(10, 6)


#include "task/Task.h"
#include "hardware/pir/Pir.h"
#include "hardware/photoresistor/PhotoResistor.h"
#include "hardware/led/GreenLed.h"
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
        //Set the led
        void turnOnLed();
        void turnOffLed();
        //State
        void detected();
        void notDetected();
        void alert();
        void checkPerson();
        //Getters
        State getState();
        PhotoResistor getPhotoresistor();
        Led getLed();
        int getPinPir();
        int getPinLed();
        int getPinPhotoresistor();
        int getLuminosity();
};

#endif