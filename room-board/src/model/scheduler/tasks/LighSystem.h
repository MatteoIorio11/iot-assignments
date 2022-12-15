#ifndef __LIGHTSYSTEM__
#define __LIGHTSYSTEM__

#include "LightSystemState.h"
#include "model/task/Task.h"
#include "hardware/led/Led.h"
#include "hardware/pir/Pir.h"
#include "hardware/photoresistor/Photoresistor.h"

class LightSystem: public Task{
    private:
        int pin_led, pin_pir, pin_photo;
        LightSystemState state;
        Led *led;
        Pir *pir;
        Photoresistor *photoresistor;
        void attachLed();
        void attachPir();
        void attachPhotoresistor();
    public:
        LightSystem(int pin_led, int pin_pir, int pin_photo);
        void init();
        void tick();
};

#endif