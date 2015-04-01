#ifndef NODE_H
#define	NODE_H

#include "Node_PJS.h"
#include "PJS_Node.h"
#include "CCU_Node.h"
#include "Node_CCU.h"
#include "Task.h"

#include<stdio.h>
#include<iostream>
#include<list>
#include <vector>
#include <queue>
#include <thread>
#include <chrono>
#include<mutex>

//std::mutex node_mutex;

class CPU {
public:
    CPU(int _id);
    CPU(const CPU& orig);
    virtual ~CPU();
    bool isBusy(){return status;};
    void Busy(){status = true;}
    int getId(){ return id;}
    void setId(int id) {this->id = id;}
    void Executer();
   
private:
    int id;
    bool status = false;
};

class Node {
public:
    Node_PJS NodePJS;
    Node_CCU NodeCCU;
    Node(int _id);
    Node(const Node& orig);
    virtual ~Node();
    void Scheduler();
    void CreateExecuters();    
    void SumbitTask();
    void PrintQ();
    int getId(){ return id;}
private:
    int id;
    int CORESNUM = 1;
    int MAINMEMORY = 8192; //8GB
    std::vector<Task> QTasks;
    //queue of task
};

#endif	/* NODE_H */

