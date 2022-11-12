#include <Arduino.h>
#include "logic/smart-light-system/LogicSLS.h"
#include "logic/timer/Timer.h"
#define PIN_LED 12
#define PIN_PIR 2
#define PIN_PHOTORESISTOR 0

Timer timer;

void setup() {
  Serial.begin(9600);
  initSLS(PIN_PIR, PIN_LED, A0);
  timer.setupPeriod(100);
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
  timer.waitForNextTick();
  tick();
}