#include <Arduino.h>
#include "model/scheduler/Scheduler.h"
#include "model/scheduler/tasks/RoomController.h"

Scheduler* scheduler;
RoomController* room_controller;
void setup() {
  Serial.begin(9600);
  room_controller = new RoomController(PIN_LED, PIN_SERVO_MOTOR);
  scheduler = new Scheduler();
  scheduler->init();
  scheduler->addTask(room_controller);
}

void loop() {
  delay(1000);
  scheduler->schedule();
}