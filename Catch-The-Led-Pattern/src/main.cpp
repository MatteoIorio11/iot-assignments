#include <Arduino.h>
#include <avr/power.h>
#include <avr/sleep.h>
#include "GreenLed.cpp"
#include "RedLed.cpp"
#include "Status.cpp"
#include "User.cpp"
#include "Bot.cpp"
#include "TimerController.cpp"
#include "TimerOne.h"

/*

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
*/
#define TEN_SECONDS 10000000
#define NLEDS 4
/*---- LEDS -----*/
#define PIN_LED_1_GREEN 13
#define PIN_LED_2_GREEN 12
#define PIN_LED_3_GREEN 11
#define PIN_LED_4_GREEN 10
#define PIN_RED_LED 9
/*---- POTENTIOMETER -----*/
#define POTENTIOMETER_INPUT_PIN A0;
/*---- BUTTONS -----*/
#define PIN_BUTTON_1 2
#define PIN_BUTTON_2 3
#define PIN_BUTTON_3 4
#define PIN_BUTTON_4 5

volatile int begin_game_cont = 0;
int penalties = 0;
bool first_time = true, first_time2 = true, penalty = false;;
User *user; 
Bot *bot;
TimerController *timer;
STATUS status;
RedLed *redLed;
int score = 0;


void startGame(){
  if(status == INPUT_WAIT){
    Serial.println("B1 is pressed, the game starts..");
    status = GAME_START;
    redLed->setOff();
    Timer1.detachInterrupt();
    sleep_disable();
  }
}

void selectLeds(){
  Serial.println("Recreate the pattern....");
  Serial.flush();
  begin_game_cont++;
  if(begin_game_cont == 1){
    if(digitalRead(PIN_BUTTON_1) == HIGH){
      user->addPos(0);
    }
    if(digitalRead(PIN_BUTTON_2) == HIGH){
      user->addPos(1);
    }
    if(digitalRead(PIN_BUTTON_3) == HIGH){
      user->addPos(2);
    }
    if(digitalRead(PIN_BUTTON_4) == HIGH){
      user->addPos(3);
    }
  }else{
    status = GAME_SCORE;
  }
}

void allLedsOff(){
    digitalWrite(PIN_LED_1_GREEN, LOW);
    digitalWrite(PIN_LED_2_GREEN, LOW);
    digitalWrite(PIN_LED_3_GREEN, LOW);
    digitalWrite(PIN_LED_4_GREEN, LOW);
}

void checkPatterns(){
  Serial.println("Check the pattern ");
  Serial.flush();
  for(int i = 0; i < NLEDS; i++){
    if(bot->getSequence()[i] != user->getPositions()[i]){
      penalty = true;
      break;
    }
  }
  status = GAME_SCORE;
}

void deepSleep(){
  delay(10000);
  if(status == INPUT_WAIT){
    redLed->setFade();
    delay(100);
    /*
    Serial.println("Going to sleep");
    Serial.flush();
    redLed->setOff();
    set_sleep_mode(SLEEP_MODE_IDLE);
    sleep_enable();
    sleep_mode();
    Serial.println("Now up");
    Serial.flush();
    redLed->setFade();
    */
  }
}

void setup() {
  redLed = new RedLed(PIN_RED_LED);
  user = new User();
  bot = new Bot(); 
    timer = new TimerController();
  status = SELECT_DIFFICULTY;
  Serial.begin(9600);
  Serial.println("----- WELCOME TO THE CATCH LED PATTERN GAME, PRESS BUTTON 1 TO START THE GAME !!! -----");
  Serial.flush();
  delay(100);
  /*--SET LEDS--*/
  pinMode(PIN_LED_1_GREEN, OUTPUT);
  pinMode(PIN_LED_2_GREEN, OUTPUT);
  pinMode(PIN_LED_3_GREEN, OUTPUT);
  pinMode(PIN_LED_4_GREEN, OUTPUT);
  /*--SET BUTTONS--*/
  pinMode(PIN_BUTTON_1, INPUT);
  pinMode(PIN_BUTTON_2, INPUT);
  pinMode(PIN_BUTTON_3, INPUT);
  pinMode(PIN_BUTTON_4, INPUT);
  /* */

  /*MANAGE INTERRUPTS */
  attachInterrupt(digitalPinToInterrupt(PIN_BUTTON_1), startGame, CHANGE);

  /*SLEEP MODE */
  timer->ledsOff();
  //Timer1.setPeriod(10000000);
  //Timer1.initialize(TEN_SECONDS);
  //Timer1.attachInterrupt(deepSleep);

  attachInterrupt((PIN_BUTTON_2), NULL, CHANGE);
  //attachInterrupt(digitalPinToInterrupt(PIN_BUTTON_3), NULL, CHANGE);
  //attachInterrupt(digitalPinToInterrupt(PIN_BUTTON_4), NULL, CHANGE);


}


void loop() {
  // put your main code here, to run repeatedly:
  switch (status)
  {
    case SELECT_DIFFICULTY:
      timer->selectDifficulty(analogRead(A0));
      Serial.print("Difficolta selezionata : "); 
      Serial.println(timer->difficultySelected());
      status = INPUT_WAIT;
      break;
    case INPUT_WAIT:
      redLed->setFade();
      delay(50);
      break;
    case GAME_START:
      //Timer1.detachInterrupt();
      Serial.println("The game is starting..");
      Serial.flush();
      bot->generateSequence();
      allLedsOff();
      delay(timer->ledsOff()*1000);

      for(int i = 0; i < NLEDS; i++){
        if(bot->getSequence()[i]){
          Serial.println(i);
          if(i == 0){
            digitalWrite(PIN_LED_1_GREEN, HIGH);
          }else if(i == 1){
            digitalWrite(PIN_LED_2_GREEN, HIGH);
          } else if(i == 2){
            digitalWrite(PIN_LED_3_GREEN, HIGH);
          }else if(i == 3){
            digitalWrite(PIN_LED_4_GREEN, HIGH);
          }
        }
      }
        status = RECREATE_PATTERN;
        delay(timer->showPattern()*1000);
        allLedsOff();
        break;
      case RECREATE_PATTERN:
        timer->beginGame();
        Serial.println(timer->getTimer3());
        Timer1.detachInterrupt();
        Timer1.initialize(timer->getTimer3() * 1000000);
        Timer1.attachInterrupt(selectLeds);
        break;
      case GAME_SCORE:
        Timer1.detachInterrupt();
        checkPatterns();
        if(!penalty){
          Serial.println("YOU ARE NOT WRONG DIO PORCO ");
          score++;
        }else if(penalties == 3){
          status = GAME_OVER;
          Serial.println("HAI PERSON ADDDIO ");
          return;
        }else{
          penalties++;
          Serial.println("HAI SBAGLIATO.");
        }
        Serial.flush();
        timer->reduceTimers();
        status = GAME_START;
        //Timer1.attachInterrupt(deepSleep);
        break;
  }
}