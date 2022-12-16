#include <Arduino.h>
#include "model/scheduler/Scheduler.h"

void setup() {
  scheduler = new Scheduler();
  scheduler->init();
  scheduler->addTask(light_system);
}

void loop() {
  // put your main code here, to run repeatedly:
}