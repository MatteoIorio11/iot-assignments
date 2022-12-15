#include <Arduino.h>
#include "model/scheduler/Scheduler.h"
#include "model/scheduler/tasks/LighSystem.h"
#include "model/wifi/WifiEsp.h"
#include "model/mqtt/MqttClient.h"

Scheduler* scheduler;
LightSystem *light_system;
WiFiEsp *wifi;
MqttClient *mqtt;

void setup() {
  Serial.begin(9600);
  wifi = new WiFiEsp();
  mqtt = new MqttClient();
  light_system = new LightSystem(PIN_LED, PIN_PIR, PIN_PHOTORESISTOR, mqtt);
  scheduler = new Scheduler();
  scheduler->init();
  scheduler->addTask(light_system);
}

void loop() {
  delay(1000);
  scheduler->schedule();
}