#include <Arduino.h>

int pin = 45;


void setup() {
  pinMode(pin, OUTPUT);

}

void loop() {
  delay(100);
  digitalWrite(pin, HIGH);
  delay(100);
  digitalWrite(pin, LOW);
}