#ifndef NODE_H
#define	NODE_H

#include "PJS_Node.h"
#include "CCU_Node.h"
#include "Node_CCU.h"
#include "Task.h"
#include "Block.h"
#include <algorithm>
#include<stdio.h>
#include<iostream>
#include<list>
#include<deque>
#include <vector>
#include <queue>
#include <chrono>
#include <queue>
#include <ctime>
#include "Globals.h"

class CPU;

class Node {
public:
    
    PJS_Node PJSNode;
    static Node_CCU NodeCCU;
    static CCU_Node CCUNode;
    Node(int _id,int numofcores,int mainmemory);
    Node(const Node& orig);
    virtual ~Node();
    void SendMatrix();
    void Scheduler();
    void Execute();
    void CreateExecuters(); 
    void addRegularTask(Task t);
    Task* getRegularTask();
    Task* getRegularTaskfromback();
    Task* PeekRegularTask();
    void addOppurtunisticTask(Task t);
    void addOppurtunisticTasktofront(Task t);
    Task* getOppurtunisticTask();
    Task* PeekOppurtunisticTask();
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
    void sendCache();
private:
    int id;
    int CORESNUM = 1;
    int MAINMEMORY = 8192; //8GB
    std::deque<Task> regularQueue;
    std::deque<Task> OppurtunisticQueue;
    matrix_t local_wait_time_matrix;
    //queue of task
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
    void validate(int coresnum,int mainmemory);
    bool IsScheduled(Task t,Node *ptr,int coresnum,int mainmemory,bool IsRegular);
    int numberoffreememory(int mainmemory,bool isRegular);
    int numberoffreecores(int coresnum,bool isRegular);
    void Zerointhearrays(Task t,Task preempted_task);
    void RecordNumberOfUsedGB(int memory);
    void RecordNumberOfUsedCores(int cores);
    struct Xgreater
    {
        bool operator()( const std::pair<Task,int>& lx, const std::pair<Task,int>& rx ) const {
    	return lx.second < rx.second;
        }
    };
    void printtologfile(Node *ptr,Task t,time_t now);
    void addToCache(Block b,Node *ptr,GlobalCache global_cache);
    void deleteFromCache(Block b);
    void UpdateCache(Block b,GlobalCache global_cache);
    bool IsPresentInCache(Block b);
    void sendCache(Node *ptr);
    
private:
    int id;
    bool status = false;
    Node *node_ptr;
    std::vector<std::pair<Task,int> > Cores;
    std::vector<std::pair<Task,int> > Memory;
    std::vector<std::pair<Block,int>> local_cache;
    
};


#endif	/* NODE_H */

