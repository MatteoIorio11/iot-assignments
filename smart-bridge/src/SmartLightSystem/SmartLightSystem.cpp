#include "SmartLightSystem.h"
#include "pir/Pir.h"
#include  "photoresistor/PhotoResistor.h"
#include "led/GreenLed.h"
#include "State.h"
#include "Arduino.h"


SmartLightSystem::SmartLightSystem(int pin_pir, int pin_led, int pin_photo){
    this->pin_pir = pin_pir;
    this->pin_led = pin_led;
    this->pin_photo = pin_photo;
    this->state = NOT_DETECTED;
}

void SmartLightSystem::init(){
    this->pir = new Pir(this->pin_pir);
    this->greenled = new GreenLed(this->pin_led);
    this->photoResistor = new PhotoResistor(this->pin_photo);
}

State SmartLightSystem::getState(){
    return this->state;
}

void SmartLightSystem::checkPerson(){
    this->state = this->pir->readValue() == HIGH ? DETECTED : NOT_DETECTED;
}

void SmartLightSystem::turnOnLed(){
    this->greenled->ledOn();
}

void SmartLightSystem::turnOffLed(){
    this->greenled->ledOff();
}

int SmartLightSystem::getLuminosity(){
    return this->photoResistor->readValue();
}

void SmartLightSystem::detected(){
    this->state = DETECTED;
}

void SmartLightSystem::notDetected(){
    this->state = NOT_DETECTED;
}

PhotoResistor SmartLightSystem::getPhotoresistor(){
    return *this->photoResistor;
}

int SmartLightSystem::getPinPir(){
    return this->pir->pin_pir;
}

int SmartLightSystem::getPinLed(){
    return this->greenled->getPin();
}

int SmartLightSystem::getPinPhotoresistor(){
    return this->photoResistor->pin_photo;
}

