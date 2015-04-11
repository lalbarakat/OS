#include <cstdlib>
#include <chrono>
#include <thread>
#include <iostream>
#include "Node.h"
#include "Task.h"
#include "Clock.h"
#include "PJS.h"
#include "CCU.h"

//Defines the frequencies at which various functions should be called.
//Meant to be representative of each tasks relative runtime.
enum time_enums{
    CCU_UPDATE_TIME=1,
    NODE_SCHEDULER_TIME=1,
    NODE_MATRIX_SEND_TIME=30,
    NODE_EXECUTOR_TIME=1,
    PJS_SCHEDULING_TIME=2,
    JOB_GENERATOR_TIME=30
};
bool running=true;

void waitForInput(){
    std::cin.get();
    running=false;
}

std::vector<Node *> Nodes_list;
 void create_node(int id,int num_cores) {
    std::cout<<"Node # " << id <<std::endl;
    Node *n =new Node(id,num_cores);
    //adding to the list of nodes.
    Nodes_list.push_back(n);
}

 
 
 /*
 * 
 */ 
int main(int argc, char** argv) {
    int num_nodes = 5;
    for (int i = 0; i < num_nodes; ++i) {
        create_node(i,1+i);
    }
    PJS PJS_obj(Nodes_list);
    std::cout<<"Main thread still here"<<std::endl;
    CCU ccu_obj(Nodes_list,&PJS_obj);
    std::cout<<"Type any key to finish this program:"<<std::endl;
    std::thread t(waitForInput);
    
    unsigned int counter=0;
    
    while(running){
        //Do things here
        if(counter%JOB_GENERATOR_TIME==0){
            //Generate a job to be given to the PJS
            ;
        }
        if(counter%NODE_SCHEDULER_TIME == 0){
            for(std::vector<Node*>::iterator it= Nodes_list.begin(); it!=Nodes_list.end(); it++){
                (*it)->Scheduler();
            }
        }
        if(counter%NODE_EXECUTOR_TIME == 0){
            for(std::vector<Node*>::iterator it = Nodes_list.begin(); it != Nodes_list.end(); it++){
                //Insert executor code.
                ;
            }
        }
        if(counter%NODE_MATRIX_SEND_TIME==0){
            for(std::vector<Node*>::iterator it= Nodes_list.begin(); it!=Nodes_list.end(); it++){
                (*it)->SendMatrix();
            }
        }
        if(counter%CCU_UPDATE_TIME==0){
            //Check for matricies to update CCU
            ;
        }
        if(counter%PJS_SCHEDULING_TIME==0){
            //Have PJS send jobs to main.
        }
        std::this_thread::yield();
        //increment clock
        counter++;
        //collect stats
    }
    t.join();
    return 0;
}

