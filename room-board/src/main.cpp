#include <Arduino.h>
#include "model/scheduler/Scheduler.h"
#include "model/scheduler/tasks/LighSystem.h"
#include "model/wifi/WifiEsp.h"
#include "model/mqtt/MqttClient.h"
#include "model/timer/Timer.h"
#include "model/timer/Timer.h"

/*
  AUTHORS :
    IORIO MATTEO
    VINCENZI FABIO
*/

Timer *timer;
Scheduler* scheduler;
LightSystem *light_system;
WiFiEsp *wifi;
MqttClient *mqtt;

void IRAM_ATTR changeTheState(){
  timer->changeState();
}

void configTimer(){
  timerAttachInterrupt(timer->getTimer(), changeTheState, true);

}

void setup() {
  Serial.begin(9600); 
  timer = new Timer();
  configTimer();
  wifi = new WiFiEsp();
  mqtt = new MqttClient();
  light_system = new LightSystem(PIN_LED, PIN_PIR, PIN_PHOTORESISTOR, mqtt);
  scheduler = new Scheduler();
  scheduler->init();
  scheduler->addTask(light_system);
}

void loop() {
  timer->waitForTheNextTick();
  scheduler->schedule();
}