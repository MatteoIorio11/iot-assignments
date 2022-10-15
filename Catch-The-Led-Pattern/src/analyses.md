

  CLASSI : 
  1- Classe per i LED {ABSTRACT}: 
      + stato
      - manage stato (get/set)
      - manage fade(+ luminosità) *only for red led*
  2- Classe per creare il pattern dei LED e gestisce la comparazione con quella presa in input dall'utente:
      - generate pattern
      - manage the difficulty 
      - manage the game over
      - manage the timers
      - comparison pattern
        * Bot.pattern == Utente.pattern ? 1 : 0
  3- Classe utente nella quale si gestisce il pattern di Input
      - manage the input pattern
  4- ? Gestione fade del potenziometro ?

  ++++++++++++++++ STATI DEL PROGRAMMA +++++++++++++++++++

  * start -> [PHASE 1] red led is blinking -> 
                    
                    --------------- SELECT THE DIFFICULTY ---------------
                    1) By using the Potentiometer we can select the difficulty of our project : 
                      1 ) easy 
                      2 ) normal
                      3 ) medium
                      4 ) difficult 
                      for each difficulty we have a different style of X2 - X3 seconds reduction
                    
                    when T1 ( FIRST BUTTON ) is touched the game begins -> 
                    before 10 seconds : -> all leds go off -> 
                                          1) Print on the serial line :"GO" and the score is set to 0 (zero)
                                          ---- GAME BEGIN ---- 
                                          1) all leds off for a X1 seconds ( X1 is random) [ HERE IS WHERE WE CREATE THE BOT'S PATTERN]
                                          2) Display the Bot's pattern for X2 seconds (X2 is setted by us ) -> and then all leds off
                                                ---- MANAGE THE PENALTY -----
                                                * If the player touch any of the buttons, a penalty is set -> the red led is on for a second,
                                                  and on the Serial port we must write :"PENALTY". 
                                                  [ AFTER 3 PENALTY THE CONSOLE WRITES :"GAME OVER FINALS SCORE : X" for 10 seconds and go to
                                                  (PHASE 1)] 
                                            ---- USER INPUT ----
                                              1) The player must insert the pattern in X3 seconds :
                                                    * before X3 seconds -> begin the comparison between the two patterns : 
                                                        SAME PATTERN : SCORE + 1 -> print on the serial :"CORRECT" -> reduction of X2 and X3.
                                                        DIFFERENT PATTERN :  the player get a PENALTY -> NOTHING HAPPEN TO THE TIMERS 
                    after 10 secons : arduino go to deep sleep -> in order to wake up the system we have to put an handler on 
                                      every button -> if any of the button is pressed we go to the (PHASE 1 )

  LOGICA : 
  1)  La logica della scelta del pattern è un semplice array di boleani/interi [0, 1, 0, 0] -> LED 1 ACCESO, LED 2, LED 0, LED 3 ==> SPENTI
  2)  X1 timer (10 seconds, the first timer ) -> if the player starts the game -> the handler must controll the state of the loop looking at the STATE
  3)  The main is views has a big switch, in different case we have different option to do. 
      -> Create some king of ENUM/CLASS where we have the variuos states of the GAME : [INPUT_WAIT, GAME_START << BEGINS WHEN X3 IS OVER >>, DEEP_SLEEP, GMAE_OVER]  
