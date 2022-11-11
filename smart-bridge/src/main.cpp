#include <Arduino.h>
#include "SmartLightSystem/SmartLightSystem.h"
#include "logic/smart-light-system/LogicSLS.h"
#define PIN_LED 0
#define PIN_PIR 0
#define PIN_PHOTORESISTOR 0

SmartLightSystem* sls;

void setup() {
  sls = new SmartLightSystem(PIN_PIR, PIN_LED, PIN_PHOTORESISTOR);
  initSLS(sls);
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
}