#include <Arduino.h>
#include "led/GreenLed.h"

GreenLed* greenLed;

void setup() {
  greenLed = new GreenLed(1);
  greenLed->init();
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
}