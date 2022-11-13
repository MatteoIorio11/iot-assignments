#ifndef __WATERFLOWCONTROLSYSTEM__
#define __WATERFLOWCONTROLSYSTEM__

#include "hardware/sonar/Sonar.h"
#include "hardware/led/GreenLed.h"
#include "hardware/led/RedLed.h"
#include "functionalities/water-flow-state/State.h"

//Metti solo dei gran metodi per accedere ai dati letti, accedere e spegnere i led ecc ecc
//Non mettere qua dentro la macchina a stati finiti, metti dei metodi per cambiare lo stato della variabile
//Metti dei metodi per accedere alla copia delle classi


class WaterflowControlSystem{
    private:
        int echoPin;
        int trigPin;
        //Cambia warning levels con state
        enum  { NORMAL, WL1, WL2} WarningLevels;
        Sonar* sonar;
        
    public:
        WaterflowControlSystem(int echoPin, int trigPin);
        void init();
        void tick();
        void detectWarningState();
        double getWaterLevel();
        State getState();
};


#endif