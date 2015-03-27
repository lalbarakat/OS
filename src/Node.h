#ifndef NODE_H
#define	NODE_H

#include "Node_PJS.h"
#include "PJS_Node.h"
#include "CCU_Node.h"
#include "Task.h"

#include<stdio.h>
#include<iostream>
#include<list>
#include <vector>
#include <queue>
#include <thread>
#include <memory>

class CPU {
public:
    CPU();
    bool isBusy(){return status;};
    void Busy(){status = true;}
    void Execute (Task t){
        std::cout<<t.getCPU_time()<<std::endl;    
    };
    virtual ~CPU();
private:
    int id;
    bool status = false;
};

  

class Node {
public:
    Node();
    Node(const Node& orig);
    virtual ~Node();
   // void SumbitTask(Task t);
    void Scheduler();
    void SumbitTask();
    void PrintQ();
    //scheduler
private:
    int CORESNUM = 1;
    int MAINMEMORY = 8192; //8GB
    std::vector<Task> QTasks;
   
    //queue of task
};

#endif	/* NODE_H */

