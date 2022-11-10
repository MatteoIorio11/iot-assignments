#include "SmartLightSystem.h"
#include "pir/Pir.h"
#include "led/GreenLed.h"
#include "Arduino.h"


SmartLightSystem::SmartLightSystem(int pin_pir, int pin_led){
    this->pin_pir = pin_pir;
    this->pin_led = pin_led;
    this->state = NOT_DETECTED;
}

void SmartLightSystem::init(){
    this->pir = new Pir(this->pin_pir);
    this->greenled = new GreenLed(this->pin_led);
}

void SmartLightSystem::tick(){
    this->checkPerson();
    switch (this->state)
    {
        case DETECTED:
            this->greenled->ledOn();
        break;
    
        case NOT_DETECTED:
            this->greenled->ledOff();
        break;
    }
}

void SmartLightSystem::checkPerson(){
    this->state = this->pir->readValue() == HIGH ? DETECTED : NOT_DETECTED;
}
