#include <TimerOne.h>
#include <EnableInterrupt.h>
#include "photoresistor/PhotoResistor.h"
#include "led/GreenLed.h"
#include "pir/Pir.h"
GreenLed* la;
PhotoResistor* ls;
Pir* pir;

void init(int pin_pir, int pin_led, int pin_photo){
    la = new GreenLed(pin_led);
    pir = new Pir(pin_pir);
    ls = new PhotoResistor(pin_photo);

}


