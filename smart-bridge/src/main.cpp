#include <Arduino.h>
#include <TimerOne.h>
#include <ArduinoJson.h>
#include "bridge/Bridge.h"
/*
AUTHORS :
  Iorio Matteo
  Vincenzi Fabio
  Rapolla Luca
*/


/*

  DIGITAL PIN:
    12 -> PIN_LED_SLS        (A)
    11 -> PIN_GREENLED_WCS   (B)
    10 -> PIN_REDLED_WCS     (C)
    9  -> PIN_SONAR          (D)
    8  -> PIN_SONAR_TRG      (E)
    6  -> PIN_BUTTON         (F)
    2  -> PIN_PIR            (G)
  
  ANALOG PIN :
    A0 -> PIN_PHOTORESISTOR  (H)
    A1 -> PIN_SERVO_MOTOR    (I)
    A2 -> PIN_POTENTIOMETER  (L)
    A4 -> Monitor::SDA       (M)
    A5 -> Monitor::SCL       (N)
                                +-----+
+----[PWR]-------------------| USB |--+
|                            +-----+  |
|         GND/RST2  [ ][ ]            |
|       MOSI2/SCK2  [ ][ ]  A5/SCL[ ] |   C5 
|          5V/MISO2 [ ][ ]  A4/SDA[ ] |   C4 
|                             AREF[ ] |
|                              GND[ ] |
| [ ]N/C                    SCK/13[ ] |   B5
| [ ]IOREF                 MISO/12[A] |   .
| [ ]RST                   MOSI/11[B]~|   .
| [ ]3V3    +---+               10[C]~|   .
| [ ]5v    -| A |-               9[D]~|   .
| [ ]GND   -| R |-               8[E] |   B0
| [ ]GND   -| D |-                    |
| [ ]Vin   -| U |-               7[ ] |   D7
|          -| I |-               6[F]~|   .
| [H]A0    -| N |-               5[ ]~|   .
| [I]A1    -| O |-               4[ ] |   .
| [L]A2     +---+           INT1/3[ ]~|   .
| [ ]A3                     INT0/2[G] |   .
| [M]A4/SDA  RST SCK MISO     TX>1[ ] |   .
| [N]A5/SCL  [ ] [ ] [ ]      RX<0[ ] |   D0
|            [ ] [ ] [ ]              |
|  UNO_R3    GND MOSI 5V  ____________/
          \_______________________/

*/

Bridge* b;

void changeTheState(){
  b->getTimer()->changeState();
}

void setup()
{
  Serial.begin(9600);
  b = new Bridge();
  b->init();
  b->getTimer()->getTimerOne()->attachInterrupt(changeTheState); 
}


void loop() {
  b->getTimer()->waitForTheNextTick();
  b->tick();
}