#include "LighSystem.h"


/// @brief Constructor of the LightSystem
/// @param pin_led Led's pin
/// @param pin_pir Pir's pin
/// @param pin_photo Photoresistor's pin
LightSystem::LightSystem(int pin_led, int pin_pir, int pin_photo, MqttClient* client){
    this->pin_led = pin_led;
    this->pin_pir = pin_pir;
    this->pin_photo = pin_photo;
    this->state = NOT_DETECTED;
    this->client = client;
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
    switch (this->state)
    {
    case NOT_DETECTED:
        if(this->pir->readValue() == HIGH){
            this->led->ledOn();
            this->state = DETECTED;
            Serial.println("DETECTED");
            //this->client->sendMessage(JsonSerializer::serialize(this->state));
        }
        break;
    
    case DETECTED:
        if(this->pir->readValue() == HIGH){
            this->led->ledOff();
            this->state = NOT_DETECTED;
            Serial.println("DETECTED");
            //this->client->sendMessage(JsonSerializer::serialize(this->state));
        }
        break;
    }
    
}
