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
#include <chrono>
#include<mutex>

//std::mutex node_mutex;

class CPU {
public:
    CPU(){
      //  std::thread tex(&CPU::Execute,this); 
    //    tex.join();
    };
    bool isBusy(){return status;};
    void Busy(){status = true;}

    int getId(){ return id;}
    void setId(int id) {this->id = id;}

    void Execute (){
        int x=0;
        while(x<5){
            std::cout<< "Hi, This Ex"<<std::endl;
            x++;
        }    
    };
   // virtual ~CPU();
private:
    int id;
    bool status = false;
};

  

class Node {
public:
    Node(int _id){
        id = _id;
        std::thread ts(&Node::Scheduler,this); 
        ts.join();
        std::thread tx(&Node::Executer,this); 
        tx.join();
        
    };
    //Node(const Node& orig);
    virtual ~Node();
   // void SumbitTask(Task t);
    void Scheduler(){   
        int x =0;
        while(x<10){
            std::cout<<"scheduler \t nodeid  "<<std::endl;
            x++;
        int y=10000000;
        for(int i=0;i<y;i++){}

        }
    };
    
    void Executer(){
        int x =0;
        while(x<10){
            std::cout<<"Executer"+std::to_string(this->getId())<<std::endl; 
            x++;
        int y=10000000;
        for(int i=0;i<y;i++){}
        }
    }; 
    
    void SumbitTask();
    void PrintQ();
    int getId(){ return id;}
   // void setId(int id) {this->id = id;}
    //scheduler
private:
    int CORESNUM = 1;
    int MAINMEMORY = 8192; //8GB
    int id;
    std::vector<Task> QTasks;
   
    //queue of task
};

#endif	/* NODE_H */

