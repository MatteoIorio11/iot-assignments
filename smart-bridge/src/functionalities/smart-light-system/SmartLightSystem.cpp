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
/// @brief Ccreate the objects inside the system in order to have more encapsulation, with this strategy the user can not read or modify this objects
void SmartLightSystem::init(){
    this->pir = new Pir(this->pin_pir);
    this->greenled = new GreenLed(this->pin_led);
    this->photoResistor = new PhotoResistor(this->pin_photo);
}

/// @brief  This method is used in order to get the state of the system, because if we are in the ALARM situation the system must be shut
/// @return the current state of the Smart-Light-System
State SmartLightSystem::getState(){
    return this->state;
}
/// @brief By using this method we can understand If a person is on the bridge. (NOT USED, but maybe in the future if we want to change how we detect the 
/// person we can use this method )
void SmartLightSystem::checkPerson(){
    this->state = this->pir->readValue() == HIGH ? DETECTED : NOT_DETECTED;
}
/// @brief Turning on the led on the bridge because a person has been detected by the senso
void SmartLightSystem::turnOnLed(){
    this->greenled->ledOn();
}
/// @brief Turning off the led, because are passed T1 (10 seconds) seconds
void SmartLightSystem::turnOffLed(){
    this->greenled->ledOff();
}
/// @brief By this method we can read how much luminosity there is in the room by calling the Photoresistor
/// @return how much luminoity there is in the room in Voltage
double SmartLightSystem::getLuminosity(){
    return this->photoResistor->readValue();
}
/// @brief the state of the system in DETECTED because a person has been detected
void SmartLightSystem::detected(){
    this->state = DETECTED;
}
/// @brief  the state of the system in NOT_DETECTED because the timer t1 is expired and no one has been detected
void SmartLightSystem::notDetected(){
    this->state = NOT_DETECTED;
}
/// @brief  the state of the system in ALARM, bcause of the water level
void SmartLightSystem::alarm(){
    this->state = SLS_ALARM;    
}
/// @brief Get the value of the photoresistor
/// @return The value and not the pointer of the photoresistor in order to have more security
PhotoResistor SmartLightSystem::getPhotoresistor(){
    return *this->photoResistor;
}
/// @brief Get the value of the led
/// @return THe value and not the pointer of  the led in order to have more security
GreenLed SmartLightSystem::getLed(){
    return *this->greenled;
}
/// @brief This method is used in order to get the current pin of the PIR sensor
/// @return The pin of the pir
int SmartLightSystem::getPinPir(){
    return this->pir->getPin();
}
/// @brief This method is used in order to get the current pin of the Led
/// @return The pin of the Led
int SmartLightSystem::getPinLed(){
    return this->greenled->getPin();
}
/// @brief This method is used in order to get the current pin of the Photoresistor
/// @return The pin of the photoresistor
int SmartLightSystem::getPinPhotoresistor(){
    return this->photoResistor->getPin();
}
/// @brief Reading the value of the Pir sensor in order to detect if someone is on the bridge
/// @return HIGH if someone is detected and LOW If there is not 
int SmartLightSystem::checkTheBridge(){
    return this->pir->readValue();
}