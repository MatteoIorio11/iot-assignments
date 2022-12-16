#include "LighSystem.h"


/// @brief Constructor of the LightSystem
/// @param pin_led Led's pin
/// @param pin_pir Pir's pin
/// @param pin_photo Photoresistor's pin
LightSystem::LightSystem(int pin_led, int pin_pir, int pin_photo, MqttClient* client){
    this->pin_led = pin_led;
    this->pin_pir = pin_pir;
    this->pin_photo = pin_photo;
    this->state = NOBODY;
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

void LightSystem::checkLuminosity(){
    double lum = this->photoresistor->readValue();
    Serial.println(lum);
    if(lum >= 0 and lum < LUMINOSITY_LOWERBOUND){
        //There is no much light, so the led must be on
        this->led->ledOn();            // Turning ON the led
    }else{
        this->led->ledOff();           // Turning OFF the led
    }
}

/// @brief State Machine of the LightSystem. The light remains ON until the PIR does not detect any motion
void LightSystem::tick(){
    switch (this->state)
    {
        case NOBODY:
            if(this->pir->readValue() == HIGH){
                this->state = INSIDE_ROOM;              // Someone is inside the room
                this->checkLuminosity();                // The person is still inside the room, the light remains ON if there is no light outside
                this->client->sendMessage(JsonSerializer::serialize(this->state, this->led->getState()));
            }
            break;
        
        case INSIDE_ROOM:
            if(this->pir->readValue() == HIGH){      // the person leaved the room, the led goes off
                this->led->ledOff();
                this->state = NOBODY;               // Leave the room
                this->client->sendMessage(JsonSerializer::serialize(this->state, this->led->getState()));
            }
            break;
    }
    
}
