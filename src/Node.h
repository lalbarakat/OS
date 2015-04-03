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
#include <queue>
#include "Globals.h"

//std::mutex node_mutex;
class CPU;

class Node {
public:
    PJS_Node PJSNode;
    Node_CCU NodeCCU;
    std::mutex queue_mutex;
    Node(int _id,int num);
    Node(const Node& orig);
    virtual ~Node();
    void Scheduler();
    void CreateExecuters(); 
    void addTask(Task t);
    Task getTask();
   // void SumbitTask();
    //void PrintQ();
    int getId(){ return id;}
private:
    int id;
    int CORESNUM = 1;
    int MAINMEMORY = 8192; //8GB
    std::queue<Task> queue;
    std::mutex qmutex;
    //queue of task
};
class CPU {
public:
    CPU(Node*);
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


#endif	/* NODE_H */

