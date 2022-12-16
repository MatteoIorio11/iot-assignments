#include "JsonSerializer.h"
/*
TEMPLATE OF A SENDING JSON
{
  "who": "ESP32-S3",
  "inside_room":"true/false",
  "led_state": "ON/OFF",
  "time":"hh:mm:ss"
}
*/
/// Serialize the JSON that will be sent to the MQTT Broker
String JsonSerializer::serialize(LightSystemState state, LedState ledState){
  DynamicJsonDocument doc(JSON_DIMENSION);
  doc["who"] = WHOIS;
  doc["inside_room"] = state == INSIDE_ROOM; 
  doc["state"] = ledState == LED_OFF ? "OFF" : "ON";
  doc["time"] = LocalTime::localTime();
  char buffer[JSON_DIMENSION]; 
  serializeJson(doc, buffer); //serializing the JSON
  //String json = Serial.readString();
  return Converter::convertoArrayToString(buffer, JSON_DIMENSION);
}