#include <Arduino.h>
/*

  CLASSI : 
  1- Classe per i LED
  2- Classe per creare il pattern dei LED e gestisce la comparazione con quella presa in input dall'utente:
        * Bot.pattern == Utente.pattern ? 1 : 0
  3- Classe utente nella quale si crea il pattern di Input
  4- ? Gestione fade del potenziometro ?

  * start -> [PHASE 1] red led is blinking -> when T1 ( FIRST BUTTON ) is touched the game begins -> 
                                                                                before 10 seconds : -> all leds go off -> 
                                                                                                      1) Print on the serial line :"GO" and the score is set to 0 (zero)
                                                                                                      ---- GAME BEGIN ---- 
                                                                                                      1) all leds off for a X1 seconds ( X1 is random) [ HERE IS WHERE WE CREATE THE BOT'S PATTERN]
                                                                                                      2) Display the Bot's pattern for X2 seconds (X2 is setted by us ) -> and then all leds off
                                                                                                            * If the player touch any of the buttons, a penalty is set -> the red led is on for a second,
                                                                                                              and on the Serial port we must write :"PENALTY". 
                                                                                                              [ AFTER 3 PENALTY THE CONSOLE WRITES :"GAME OVER FINALS SCORE : X" for 10 seconds]
                                                                                                        ---- USER INPUT ----
                                                                                                          1) The player must insert the pattern in X3 seconds :
                                                                                                                * before X3 seconds -> begin the comparison between the two patterns 
                                                                                after 10 secons : arduino go to deep sleep -> in order to wake up the system we have to put an handler on 
                                                                                                  every button -> if any of the button is pressed we go to the (PHASE 1 )

  LOGICA : 
  1)  La logica della scelta del pattern è un semplice array di boleani/interi [0, 1, 0, 0] -> LED 1 ACCESO, LED 2, LED 0, LED 3 ==> SPENTI
  2)  
*/
void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
}