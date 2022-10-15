#include<stdlib.h>
#include "User.h"
#define NLED 4
using namespace std;

void User::addPos(int selected_pos){
    if(selected_pos < NLED && selected_pos >= 0){
        positions[selected_pos]=true;
    }
}
    
void User::resetAllPositions(){
    for(int i = 0; i < NLED; i++){
        positions[i]=false;
    }
}

bool* User::getPositions(){
    return positions;
}