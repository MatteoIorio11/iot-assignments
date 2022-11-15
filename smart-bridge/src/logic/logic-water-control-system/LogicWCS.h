#ifndef __LOGICWCS__
#define __LOGICWCS__

#define MINIMUM_SONAR_DISTANCE 2
#define WL1_BOUND 150
#define WL2_BOUND 300
#define MAXIMUM_SONAR_DISTANCE 400

void initWCS(int pin_servo, int pin_pot, int pin_button, int sonar_echoPin, int sonar_trigPin, int red_pin_led, int green_pin_led);
void tickWCS();
void automatic();
void buttonHandler();
void refreshWaterState();

#endif