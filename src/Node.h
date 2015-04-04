#ifndef NODE_H
#define	NODE_H

#include "Node_PJS.h"
#include "PJS_Node.h"
#include "CCU_Node.h"
#include "Node_CCU.h"
#include "Task.h"

#include<condition_variable>
#include<stdio.h>
#include<iostream>
#include<list>
#include <vector>
#include <queue>
#include <thread>
#include <chrono>
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
    void Start_Node();
    void Scheduler();
    void CreateExecuters(); 
    void addTask(Task t);
    Task getTask();
    void Create_Waittime_matrix();
   // void SumbitTask();
    //void PrintQ();
    int getId() const { return id;}
    int getCoreNum() const {return CORESNUM;}
    int getMemory() const {return MAINMEMORY;}
private:
    int id;
    int CORESNUM = 1;
    int MAINMEMORY = 8192; //8GB
    std::queue<Task> queue;
    std::mutex qmutex;
    std::mutex output_mutex;
    std::mutex pjsNode_mutex;
    std::condition_variable* pjsNodecv;
    //queue of task
    std::unique_ptr<std::thread> node_thread_ptr;
    std::unique_ptr<std::thread> scheduler_thread_ptr;
    std::vector<CPU *> CPU_ptr_list;
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
    std::unique_ptr<std::thread> executor_thread_ptr;
};


#endif	/* NODE_H */

