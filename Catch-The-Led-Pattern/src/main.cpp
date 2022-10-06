#include <Arduino.h>
/*

  CLASSI : 
  1- Classe per i LED
  2- Classe per creare il pattern dei LED e gestisce la comparazione con quella presa in input dall'utente:
        * Bot.pattern == Utente.pattern ? 1 : 0
  3- Classe utente nella quale si crea il pattern di Input
  4- ? Gestione fade del potenziometro ?

  * start -> [PHASE 1] red led is blinking -> when T1 ( FIRST BUTTON ) is touched the game begins -> 
                                                                                before 10 seconds : the pattern is displaied to the user -> the user have to    
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