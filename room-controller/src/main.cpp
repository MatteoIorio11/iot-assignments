#include <Arduino.h>
#include "model/scheduler/Scheduler.h"
#include "model/scheduler/tasks/RoomController.h"

Scheduler* scheduler;
RoomController* room_controller;
void setup() {
  scheduler = new Scheduler();
  scheduler->init();
  scheduler->addTask(room_controller);
}

void loop() {
  // put your main code here, to run repeatedly:
}