#ifndef __ROOMCONTROLLER__
#define __ROOMCONTROLLER__

#include "RoomController.h"
#include "model/task/Task.h"
#include "hardware/led/Led.h"
#include "utilities/serializer/JsonSerializer.h"

class RoomController: public Task{
    private:
        int pin_led, pin_servo;
        RoomControllerState state;
        Led *led;
        ServoMotor *servo;
        void attachLed();
        void attachServo();
    public:
        RoomController(int pin_led, int pin_servo);
        void init();
        void tick();
};

#endif