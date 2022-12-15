#include <Arduino.h>
#include "scheduler/Scheduler.h"
#include "scheduler/tasks/LighSystem.h"

Scheduler* s;
LightSystem *ls;

void setup() {
  ls = new LightSystem(PIN_LED, PIN_PIR, PIN_PHOTORESISTOR);
  s = new Scheduler();
  s->init();
  s->addTask(ls);
}

void loop() {
  s->schedule();
}