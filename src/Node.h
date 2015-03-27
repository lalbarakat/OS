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

class CPU {
public:
    CPU(){
      //  std::thread tex(&CPU::Execute,this); 
    //    tex.join();
    };
    bool isBusy(){return status;};
    void Busy(){status = true;}
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
    Node(){
        std::thread ts(&Node::Scheduler,this); 
       // ts.join();
       // CPU *core = new CPU();
        std::thread tx(&Node::Executer,this); 
        std::thread tx2(&Node::foo,this); 
        tx2.join();
        
    };
    //Node(const Node& orig);
   // virtual ~Node();
   // void SumbitTask(Task t);
    void Scheduler(){   
        int x =0;
        while(x<10){
            std::cout<<"Howdy yall, Im scheduler"<<std::endl; 
            x++;
        int y=10000000;
        for(int i=0;i<y;i++){}

        }
    };
    
    void Executer(){
        int x =0;
        while(x<10){
            std::cout<<"Howdy yall, Im Executer"<<std::endl; 
            x++;
        int y=10000000;
        for(int i=0;i<y;i++){}
        }
    }; 
    
     void foo(){
        int x =0;
        while(x<10){
            std::cout<<"Howdy yall, Im foo"<<std::endl; 
            x++;
        int y=10000000;
        for(int i=0;i<y;i++){}
        }
    }; 
    
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

