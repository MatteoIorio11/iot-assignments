#include "RoomController.h"


/// @brief Constructor of the RoomController
/// @param pin_led Led's pin
/// @param pin_servo ServoMotor's pin
RoomController::RoomController(int pin_led, int pin_servo){
    Serial.println("cc");
    this->pin_led = pin_led;
    this->pin_servo = pin_servo;
    this->state = RUNNING;
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
            Serial.println("RUNNING");
            //if switch to ON
            //this->state = SETTING_LED_ON;

            //if switch to OFF
            //this->state = SETTING_LED_OFF;

            //if time == 8.00
            this->state = WAITING_FOR_OPENING;

            //IF TIME == 19.00
            //this->state = WAITING_FOR_CLOSING;
            
            
            break;
        case WAITING_FOR_OPENING:
            //if movement detected == true
            this->state = OPENING_ROLLER_BLINDS;
            break;
        case WAITING_FOR_CLOSING:
            //if movement detected == false
            this->state = CLOSING_ROLLER_BLINDS;
            break;
        case OPENING_ROLLER_BLINDS:
            //open roller blinds then going back to RUNNING
            this->servo->open();
            this->state = RUNNING;
            break;
        case CLOSING_ROLLER_BLINDS:
            //close roller blinds then going back to RUNNING
            this->servo->close();
            this->state = RUNNING;
            break;
        case SETTING_LED_OFF:
            //turning the led off then going back to RUNNING
            this->led->ledOff();
            this->state = RUNNING;
            break;
        case SETTING_LED_ON:

            Serial.println("ON");
            //turning the led on then going back to RUNNING
            this->led->ledOn();
            this->state = RUNNING;
            break;
    }
    
}