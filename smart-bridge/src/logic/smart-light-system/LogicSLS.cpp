#include <TimerOne.h>
#include <EnableInterrupt.h>
#include "LogicSLS.h"
#include "SmartLightSystem/SmartLightSystem.h"

#define PIN_LED 0
#define PIN_PIR 0
#define PIR_PHOTORESISTOR 0

SmartLightSystem* sls;

void init(int pin_pir, int pin_led, int pin_photo){
    sls = new SmartLightSystem(pin_pir, pin_led, pin_photo);
}

void tick(){
    switch (sls->getState())
    {
    case DETECTED:
        
        break;
    
    default:
        break;
    }
}

