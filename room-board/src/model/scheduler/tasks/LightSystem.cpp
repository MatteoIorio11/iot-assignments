#include "LighSystem.h"


/// @brief Constructor of the LightSystem
/// @param pin_led Led's pin
/// @param pin_pir Pir's pin
/// @param pin_photo Photoresistor's pin
LightSystem::LightSystem(int pin_led, int pin_pir, int pin_photo, MqttClient* client){
    this->pin_led = pin_led;
    this->pin_pir = pin_pir;
    this->pin_photo = pin_photo;
    this->light_timer = 0;
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
/// @brief Check the luminosity of the room, in order to turn on the light or turn off the light.
void LightSystem::checkLuminosity(){
    double lum = this->photoresistor->readValue();
    LedState prevState = this->led->getState();
    if(lum >= 0 and lum < LUMINOSITY_LOWERBOUND){
        //There is no much light, so the led must be on
        this->led->changeState();            // Turning ON the led
    }else{
        this->led->changeState();           // Turning OFF the led
    }
    if(prevState != this->led->getState()){

    }
}

void LightSystem::sendMessage(){
    LedState prevState = this->led->getState(); // Get the prev state
    this->checkLuminosity();                    // The person is still inside the room, the light remains ON if there is no light outside
    if(prevState != this->led->getState()){
        this->client->sendMessage(JsonSerializer::serialize(this->state, this->led->getState())); // Write only if the state is changed
    }
}

/// @brief State Machine of the LightSystem. The light remains ON until the PIR does not detect any motion
void LightSystem::tick(){
    switch (this->state)
    {
        case NOBODY:
            if(this->pir->readValue() == HIGH){
                this->light_timer = 0;                  // Reset timer
                this->state = INSIDE_ROOM;              // Someone is inside the room
                this->checkLuminosity();                // The person is still inside the room, the light remains ON if there is no light outside
                this->led->turnOn();
                this->client->sendMessage(JsonSerializer::serialize(this->state, this->led->getState()));
            }
            break;
        
        case INSIDE_ROOM:
            if(this->light_timer >= LIGHT_TIMER(TIMER_PERIOD)){
                // If after 10 seconds nobody is in the room, the light must be OFF.
                this->light_timer = 0;                  // Reset of the timer
                this->state = NOBODY;                   // No activity inside the room, the light is off
                this->led->turnOff();                    // Shut the led
                this->client->sendMessage(JsonSerializer::serialize(this->state, this->led->getState()));
            }else{
                if(this->pir->readValue() == HIGH){
                    // A person is still inside the room. the state must be INSIDE_ROOM
                    this->light_timer = 0;                      // Reset of the timer, the person is still inside the room
                }else{
                    this->light_timer++;                        // No activity, the timer is incremented
                }
                this->sendMessage();
            }
            break;
    }
    
}
