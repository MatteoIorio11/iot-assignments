#ifndef __LIGHTSYSTEM__
#define __LIGHTSYSTEM__

#include "LightSystemState.h"
#include "model/task/Task.h"
#include "hardware/led/Led.h"
#include "hardware/pir/Pir.h"
#include "hardware/photoresistor/Photoresistor.h"
#include "model/mqtt/MqttClient.h"
#include "utilities/serializer/JsonSerializer.h"

class LightSystem: public Task{
    private:
        int pin_led, pin_pir, pin_photo, light_timer;
        LightSystemState state;
        Led *led;
        Pir *pir;
        Photoresistor *photoresistor;
        MqttClient *client;
        void attachLed();
        void attachPir();
        void attachPhotoresistor();
        void checkLuminosity();
    public:
        LightSystem(int pin_led, int pin_pir, int pin_photo, MqttClient* client);
        void init();
        void tick();
};

#endif