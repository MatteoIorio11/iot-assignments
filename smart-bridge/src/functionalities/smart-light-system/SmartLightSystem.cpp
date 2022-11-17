#include "SmartLightSystem.h"
#include "hardware/pir/Pir.h"
#include "hardware/photoresistor/PhotoResistor.h"
#include "hardware/led/GreenLed.h"
#include "State.h"
#include "Arduino.h"


SmartLightSystem::SmartLightSystem(int pin_pir, int pin_led, int pin_photo){
    this->pin_pir = pin_pir;
    this->pin_led = pin_led;
    this->pin_photo = pin_photo;
    this->state = NOT_DETECTED;
}
//We create the objects inside the system in order to have more encapsulation, with this strategy the user can not read or
//modify this objects
void SmartLightSystem::init(){
    this->pir = new Pir(this->pin_pir);
    this->greenled = new GreenLed(this->pin_led);
    this->photoResistor = new PhotoResistor(this->pin_photo);
}

//Return the state of the system
State SmartLightSystem::getState(){
    return this->state;
}
//Check if a person is on the bridge
void SmartLightSystem::checkPerson(){
    this->state = this->pir->readValue() == HIGH ? DETECTED : NOT_DETECTED;
}
//Turn on the led
void SmartLightSystem::turnOnLed(){
    this->greenled->ledOn();
}
//Turn off the led
void SmartLightSystem::turnOffLed(){
    this->greenled->ledOff();
}
//Get the luminosity of the environment
double SmartLightSystem::getLuminosity(){
    return this->photoResistor->readValue();
}
//Change the state of the system in DETECTED because a person has been detected
void SmartLightSystem::detected(){
    this->state = DETECTED;
}
//Change the state of the system in NOT_DETECTED because the timer t1 is expired and no one has been detected
void SmartLightSystem::notDetected(){
    this->state = NOT_DETECTED;
}
//Change the state of the system in ALARM, bcause of the water level
void SmartLightSystem::alarm(){
    this->state = SLS_ALARM;    
}
//Get the value of the photoresistor
PhotoResistor SmartLightSystem::getPhotoresistor(){
    return *this->photoResistor;
}
//Get the value of the led
GreenLed SmartLightSystem::getLed(){
    return *this->greenled;
}
//Get the pir of the pir
int SmartLightSystem::getPinPir(){
    return this->pir->getPin();
}
//Get the pin of the led
int SmartLightSystem::getPinLed(){
    return this->greenled->getPin();
}
//Get the pin of the photoresistor
int SmartLightSystem::getPinPhotoresistor(){
    return this->photoResistor->getPin();
}
//Check if someone is on the bridge
int SmartLightSystem::checkTheBridge(){
    return this->pir->readValue();
}