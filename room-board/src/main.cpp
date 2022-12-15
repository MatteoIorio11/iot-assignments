#include <Arduino.h>
#include "model/scheduler/Scheduler.h"
#include "model/scheduler/tasks/LighSystem.h"
#include "model/wifi/WifiEsp.h"
#include "model/mqtt/MqttClient.h"
#include "utilities/converter/Converter.h"

Scheduler* s;
LightSystem *ls;
WiFiEsp *wifi;
MqttClient *mqtt;

void setup() {
  mqtt = new MqttClient(MQTT_SERVER, Converter::ConvertStringToArray(MQTT_TOPIC));
  wifi = new WiFiEsp(Converter::ConvertStringToArray(WIFI_SSID), Converter::ConvertStringToArray(WIFI_PASSWORD));
  ls = new LightSystem(PIN_LED, PIN_PIR, PIN_PHOTORESISTOR, mqtt);
  s = new Scheduler();
  s->init();
  s->addTask(ls);
}

void loop() {
  delay(1000);
  s->schedule();
}