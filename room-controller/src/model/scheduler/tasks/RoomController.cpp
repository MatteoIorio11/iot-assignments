#include "RoomController.h"


/// @brief Constructor of the RoomController
/// @param pin_led Led's pin
/// @param pin_servo ServoMotor's pin
RoomController::RoomController(int pin_led, int pin_servo){
    this->pin_led = pin_led;
    this->pin_servo = pin_servo;
    //this->state = LED_OFF;
    this->init();
}

/// @brief Init of all the components
void RoomController::init(){
    this->attachLed();
    this->attachServo();
}

/// @brief Attach the led
void RoomController::attachLed(){
    this->led = new Led(this->pin_led);
}

/// @brief Attach the servo
void RoomController::attachServo(){
    this->servo = new ServoMotor(this->pin_servo);
}

/// @brief State Machine of the RoomController
void RoomController::tick(){
    switch (this->state)
    {
        case RUNNING:
            break;
        case WAITING_FOR_OPENING:
            break;
        case WAITING_FOR_CLOSING:
            break;
        case OPENING_ROLLER_BLINDS:
            break;
        case CLOSING_ROLLER_BLINDS:
            break;
        case SETTING_LED_OFF:
            break;
        case SETTING_LED_ON:
            break;
    }
    
}