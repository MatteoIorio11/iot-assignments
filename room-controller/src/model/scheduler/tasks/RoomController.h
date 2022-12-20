#ifndef __ROOMCONTROLLER__
#define __ROOMCONTROLLER__

#include "RoomController.h"
#include "model/task/Task.h"
#include "hardware/led/Led.h"
#include "hardware/servomotor/ServoMotor.h"
#include "utilities/serializer/JsonSerializer.h"
#include "model/serialMsgService/SerialMsgService.h"
#include "hardware/bluetooth/Bluetooth.h"

class RoomController: public Task{
    private:
        int pin_led, pin_servo, RX_pin, TX_pin;
        RoomControllerState state;
        Led *led;
        ServoMotor *servo;
        Bluetooth *bluetooth;
        DynamicJsonDocument *btMsg;
        DynamicJsonDocument *serialMsg;
        SerialMsgService *msgService;
        void attachLed();
        void attachServo();
        bool readSerialMessage();
        bool readBtMessage();
    public:
        RoomController(int pin_led, int pin_servo, int RX_pin, int TX_pin);
        void init();
        void tick();
};

#endif