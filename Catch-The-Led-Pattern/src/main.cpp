
#define EI_ARDUINO_INTERRUPTED_PIN // to enable pin states functionality 
#include <EnableInterrupt.h>
#include <Arduino.h>
#include <avr/power.h>
#include <avr/sleep.h>
#include <TimerOne.h>

#include "Status.h"
#include "GameController.cpp"

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
#define BOUNCE_DURATION 20
#define TEN_SECONDS_SLEEP 10*pow(10, 6)
#define TEN_SECONDS_DELAY 10*pow(10, 3)
#define NLEDS 4
/*---- LEDS -----*/

#define PIN_LED_1_GREEN 13
#define PIN_LED_2_GREEN 12
#define PIN_LED_3_GREEN 11
#define PIN_LED_4_GREEN 10
#define PIN_RED_LED 6

#define ENABLE_INT_IN_PIN 2

/*---- POTENTIOMETER -----*/
#define POTENTIOMETER_INPUT_PIN A0;
/*---- BUTTONS -----*/
#define PIN_BUTTON_1 5
#define PIN_BUTTON_2 4
#define PIN_BUTTON_3 3
#define PIN_BUTTON_4 2


int brightness;
int fadeAmount;
int currIntensity;
volatile int timer_select_leds = 0, timer_show_pattern = 0, timer_deep_sleep = 0, bounceTime = 0;
GameController *controller;

void selectLeds(){
  timer_select_leds++;
  if(timer_select_leds == 2){
    controller->phaseSelectLeds();
    Serial.println("===> The time is over");
    Timer1.detachInterrupt();
    timer_select_leds = 0;
  }
}
void allLedsOff(){
    digitalWrite(PIN_LED_1_GREEN, LOW);
    digitalWrite(PIN_LED_2_GREEN, LOW);
    digitalWrite(PIN_LED_3_GREEN, LOW);
    digitalWrite(PIN_LED_4_GREEN, LOW);
    analogWrite(PIN_RED_LED, 0);
    delay(10);
}

void updateLeds(){
  bool* leds = controller->getBotLeds();
  int led;
  for(int i = 0; i < NLEDS; i++){
      switch (i)
      {
        case 0:
          led = PIN_LED_1_GREEN;
          break;
        case 1 :
          led = PIN_LED_2_GREEN;
          break;
        case 2 :
          led = PIN_LED_3_GREEN;
          break;
        case 3 : 
          led = PIN_LED_4_GREEN;
          break;
        default:
          break;
      }
    digitalWrite(led, leds[i]?HIGH:LOW);
  }
}


void wakeUp(){
  if(controller->getStatus() == DEEP_SLEEP and abs(millis() - bounceTime) > BOUNCE_DURATION){
    controller->phaseWakeUp();
    bounceTime = millis();
    Serial.println("==> Just wake up...");
    Serial.flush();
    timer_deep_sleep = 0;
    sleep_disable();
    power_all_enable();
  }
}

void gameScore(){
    controller->phaseGameScore();
    Timer1.detachInterrupt();
    allLedsOff();
    //INIT TIMER T2 E T3 NEL SETUP
    Timer1.initialize(controller->getTimerT3() * pow(10,6));
    Timer1.attachInterrupt(selectLeds);
    Serial.println("==> Recreate the pattern....");
    controller->phaseRecreatePattern();
}

void showPattern(){
  timer_show_pattern++;
  if(timer_show_pattern == 2){
    controller->phaseShowPattern();
    Timer1.detachInterrupt();
    allLedsOff();
    /*Show all the bot led pattern*/
    Timer1.initialize();
    Timer1.attachInterrupt(gameScore);
    timer_show_pattern=0;
  }else{
    controller->botGenerateSequence();
    updateLeds();
  }
}

void showPenalty(){
    controller->phasePenalty();
}

void continueGame(){
    controller->userResetAllPositions();
    Serial.println("--> The game is starting..");
    Serial.flush();
    /*Generate the bot sequence for the input */
    /*Shut all the leds */
    /*Detach of deep sleep interrupt*/
    allLedsOff();
    Timer1.detachInterrupt();
    controller->timerShowPattern();
    /*After T1 time, We show the pattern generated by the Bots*/
    Timer1.initialize(controller->getTimerT2()*pow(10,6));
    Timer1.attachInterrupt(showPattern);
}

void startGame(){
    //selecting the difficulty from the potentiometer
    controller->selectDifficulty(analogRead(A0));
    /*Plot on the serial line*/
    Serial.print("-> Difficulty selected : "); 
    Serial.println(controller->getSelectedDifficulty());
    Serial.flush();
    allLedsOff();
    controller->phaseStartGame();
    controller->timerLedsOff();
    Timer1.initialize(controller->getTimerT1()*pow(10, 6));
    Timer1.attachInterrupt(continueGame);
}


void deepSleep(){
  timer_deep_sleep++;
  if(timer_deep_sleep == 2){
      if(controller->getStatus() == INPUT_WAIT){
        Serial.println("=> Going to sleep");
        controller->phaseDeepSleep();
        allLedsOff();
        set_sleep_mode(SLEEP_MODE_IDLE);
        sleep_enable();    
    }
  }
}

void ledON(int led){
  switch(led){
    case 1:
      digitalWrite(PIN_LED_1_GREEN, HIGH);
    break;
    case 2:
      digitalWrite(PIN_LED_2_GREEN, HIGH);
    break;
    case 3:
      digitalWrite(PIN_LED_3_GREEN, HIGH);
    break;
    case 4:
      digitalWrite(PIN_LED_4_GREEN, HIGH);
    break;
  }
}


void buttonPressed(int button){
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  // If interrupts come faster than 200ms, assume it's a bounce and ignore
  if (interrupt_time - last_interrupt_time > 200) 
  {
    switch (controller->getStatus())
    {
      case INPUT_WAIT:
        if(button == 1){
          /*Manage the bouncing problem */
          if(abs(millis() - bounceTime) > BOUNCE_DURATION){
            bounceTime = millis();
            Serial.println("-> B1 is pressed, the game starts..");
            startGame();
          }
        }
        break;
      case DEEP_SLEEP:
        wakeUp();
        break;
      case GAME_START:
        controller->phasePenalty();
        break;
      case SHOW_PATTERN:
        controller->phasePenalty();
        break;
      case RECREATE_PATTERN:
        ledON(button);
        controller->userAddPosition(button-1);
      break;
    }
  }
  last_interrupt_time = interrupt_time;
}

void button_1_handler(){
  buttonPressed(1); 
}
void button_2_handler(){
  buttonPressed(2);
}
void button_3_handler(){
  buttonPressed(3);  
}
void button_4_handler(){
  buttonPressed(4);
}

void setup() {
  controller = new GameController();

  currIntensity = 0;
  fadeAmount = 5;
  Serial.begin(32600);
  Serial.println("----- WELCOME TO THE CATCH LED PATTERN GAME, PRESS BUTTON 1 TO START THE GAME !!! -----");
  Serial.flush();

  /*--SET LEDS--*/
  pinMode(PIN_LED_1_GREEN, OUTPUT);
  pinMode(PIN_LED_2_GREEN, OUTPUT);
  pinMode(PIN_LED_3_GREEN, OUTPUT);
  pinMode(PIN_LED_4_GREEN, OUTPUT);
  pinMode(PIN_RED_LED, OUTPUT);
  /*--SET BUTTONS--*/
  pinMode(PIN_BUTTON_1, INPUT);
  pinMode(PIN_BUTTON_2, INPUT);
  pinMode(PIN_BUTTON_3, INPUT);
  pinMode(PIN_BUTTON_4, INPUT);
  /* */

  /*SLEEP MODE */
  Timer1.initialize(TEN_SECONDS_SLEEP);
  Timer1.attachInterrupt(deepSleep);

  /*MANAGE INTERRUPTS */
  enableInterrupt(PIN_BUTTON_1,button_1_handler,RISING);
  enableInterrupt(PIN_BUTTON_2,button_2_handler,RISING);
  enableInterrupt(PIN_BUTTON_3,button_3_handler,RISING);
  enableInterrupt(PIN_BUTTON_4,button_4_handler,RISING);
  
  /*GENERATE THE TIMER T2 AND T3*/
  controller->timerShowPattern();
  controller->timerBeginGame();
}

void fade(){
    analogWrite(PIN_RED_LED, currIntensity);   
    currIntensity = currIntensity + fadeAmount;
    if (currIntensity == 0 || currIntensity == 255) {
      fadeAmount = -fadeAmount ; 
    }     
    delay(15); 
}

bool anyInteraction(){
  return digitalRead(PIN_BUTTON_1) == HIGH or
  digitalRead(PIN_BUTTON_2) == HIGH or
  digitalRead(PIN_BUTTON_3) == HIGH or
  digitalRead(PIN_BUTTON_4) == HIGH;
}



void loop() {
  switch (controller->getStatus())
  {
    case INPUT_WAIT:
    /*Fade of the red led*/
      fade();
      break;
    case PENALTY:
      Serial.println("==> You click a button to early or you have chosen the wrong pattern, a penalty is assigned :( ");
      allLedsOff();
      digitalWrite(PIN_RED_LED, HIGH);
      delay(1000);
      digitalWrite(PIN_RED_LED, LOW);
      controller->addPenalty();
      if(controller->isGameOver()){
        controller->phaseGameOver();
      }else{
        controller->phaseStartGame();
        timer_show_pattern = 0;
        continueGame();
      }
      break;
      case GAME_SCORE:
        if(controller->checkSequence()){

          Serial.println("--> Correct, you recreate the original pattern :) ");
          Serial.println("----------------------------------------------------------");
          controller->increaseScore();
          controller->timerReduceTimers();
          controller->phaseStartGame();
          continueGame();
        }else{
          if(controller->isGameOver()){
            controller->phaseGameOver();
          }else{
            controller->phasePenalty();
          }
        }        

        break;
      case GAME_OVER:
        Serial.print("::> The game is over, your score is ==> ");
        Serial.println(controller->getScore());
        Serial.println("----------------------------------------------------------");
        Timer1.detachInterrupt();
        Serial.flush();
        delay(TEN_SECONDS_DELAY);
        Serial.println("THE GAME STARTS AGAIN -> ");
        delay(50);
        controller->resetGame();
        startGame();
        break;
      case VOID:
      break;
  }
}