#include "Scheduler.h"

void Scheduler::init(){
  //this->timer = timer;
  this->nTasks = 0;
}

bool Scheduler::addTask(Task* task){
    if (nTasks < MAX_TASKS-1){
        taskList[nTasks] = task;
        nTasks++;
        return true;
    } else {
        return false; 
    }
}
  
void Scheduler::schedule(){   
    for (int i = 0; i < nTasks; i++){
        taskList[i]->tick();
    }
}