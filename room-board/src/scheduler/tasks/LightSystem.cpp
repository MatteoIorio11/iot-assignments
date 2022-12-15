#include "LighSystem.h"


/// @brief Constructor of the LightSystem
/// @param pin_led Led's pin
/// @param pin_pir Pir's pin
/// @param pin_photo Photoresistor's pin
LightSystem::LightSystem(int pin_led, int pin_pir, int pin_photo){
    this->pin_led = pin_led;
    this->pin_pir = pin_pir;
    this->pin_photo = pin_photo;
    this->status = NOT_DETECTED;
    this->init();
}

/// @brief Init of all the components
void LightSystem::init(){
    this->attachLed();
    this->attachPir();
    this->attachPhotoresistor();
}

/// @brief Attach the led
void LightSystem::attachLed(){
    this->led = new Led(this->pin_led);
}

/// @brief Attach the pir
void LightSystem::attachPir(){
    this->pir = new Pir(this->pin_pir);
}

/// @brief Attach the photoresistor
void LightSystem::attachPhotoresistor(){
    this->photoresistor = new Photoresistor(this->pin_photo);
}

/// @brief State Machine of the LightSystem
void LightSystem::tick(){
    switch (this->status)
    {
    case NOT_DETECTED:
        if(this->pir->readValue() == HIGH){
            this->led->ledOn();
            // TODO : Send the message to the broker 
            this->status = DETECTED;
        }
        break;
    
    case DETECTED:
        if(this->pir->readValue() == HIGH){
            this->led->ledOff();
            // TODO : Send the message to the broker
            this->status = DETECTED;
        }
        break;
    }
    
}