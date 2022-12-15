#ifndef __SCHEDULER__
#define __SCHEDULER__

#include "task/Task.h"
#include "constants/Constants.h"


class Scheduler {
  private:
    int nTasks;
    Task* taskList[MAX_TASKS];  

  public:
    void init();  
    virtual bool addTask(Task* task);  
    virtual void schedule();
};

#endif