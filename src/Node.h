#ifndef NODE_H
#define	NODE_H

#include "Node_PJS.h"
#include "PJS_Node.h"
#include "CCU_Node.h"
#include "Node_CCU.h"
#include "Task.h"

#include <algorithm>
#include<condition_variable>
#include<stdio.h>
#include<iostream>
#include<list>
#include<deque>
#include <vector>
#include <queue>
#include <thread>
#include <chrono>
#include <queue>
#include <ctime>
#include "Globals.h"

typedef std::vector <float> row_t;

typedef std::vector <row_t> matrix_t;
//std::mutex node_mutex;
class CPU;

class Node {
public:
    
    PJS_Node PJSNode;
    static Node_CCU NodeCCU;
    std::mutex queue_mutex;
    Node(int _id,int num);
    Node(const Node& orig);
    virtual ~Node();
    void Start_Node();
    void Scheduler();
    void CreateExecuters(); 
    void addTask(Task t);
    Task getTask();
    Task PeekTask();
    int FindMinVal(int Cores[4],int Memory[4],int numofcores, int mainmemory,
        int task_cores,int task_mem);
    float Estimatewaittime(int cores, int Memory);
    void Create_Waittime_matrix();
    int Mem_array[4] = {4,8,12,16};
    int cores_array[4] = {2,4,6,8};
    void resize( matrix_t& m, unsigned rows, unsigned cols, float value = 0.0 )
    {
        // first, resize all the available columns
        unsigned min = (m.size() < rows) ? m.size() : rows;
        for (unsigned row = 0; row < min; row++)
          {
          m[ row ].resize( cols, value );
          }
        // next, resize the rows -- adding complete new columns if necessary
        m.resize( rows, row_t( cols, value ) );
    }
   // void SumbitTask();
    //void PrintQ();
    int getId() const { return id;}
    int getCoreNum() const {return CORESNUM;}
    int getMemory() const {return MAINMEMORY;}
    void notifyPJS();
private:
    int id;
    int CORESNUM = 1;
    int MAINMEMORY = 8192; //8GB
    bool sched_running=true;
    bool ccu_com_running=true;
    std::deque<Task> queue;
    matrix_t local_wait_time_matrix;
    std::mutex qmutex;
    std::mutex output_mutex;
    std::mutex pjsNode_mutex;
    std::mutex condition_mutex;
    std::condition_variable pjsNodecv;
    //queue of task
    std::unique_ptr<std::thread> node_thread_ptr;
    std::unique_ptr<std::thread> scheduler_thread_ptr;
    std::vector<CPU *> CPU_ptr_list;
    
    friend class CPU;
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
    void Executer(Node *ptr);
    void validate(int Cores[],int Memory[],int coresnum,int mainmemory);
    bool IsScheduled(Task t, int Cores[],int Memory[],int coresnum,int mainmemory);
    int numberoffreememory(int Memory[],int mainmemory);
    int numberoffreecores(int Cores[],int coresnum);
    void printtologfile(Task t,time_t now);

private:
    int id;
    bool status = false;
    Node *node_ptr;
    std::unique_ptr<std::thread> executor_thread_ptr;
};


#endif	/* NODE_H */

