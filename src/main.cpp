#include <cstdlib>
#include <chrono>
#include <climits>
#include <sstream>
#include <iostream>
#include <time.h>       /* time */
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

 void create_node(int id,int num_cores,int memoryGB) {
    std::cout<<"Node # " << id <<std::endl;
    Node *n =new Node(id,num_cores,memoryGB);
    //adding to the list of nodes.
    Nodes_list.push_back(n);
}
 
 /*
 * 
 */ 
int main(int argc, char** argv) {
    int num_nodes = 5;
    /*int randomcores[]={2,4,6,8};
    int randommemory[]={4,8,12,16};
    for (int i = 0; i < num_nodes; ++i) {
          srand (time(NULL));
          int r = rand()%4;
          srand (time(NULL));
          int s = rand()%4;
        create_node(i,randomcores[r],randommemory[s]);
    }
    */
     Nodes_list.push_back(new Node(0,2,12));
     Nodes_list.push_back(new Node(1,8,8));
     Nodes_list.push_back(new Node(2,8,16));
     Nodes_list.push_back(new Node(3,4,8));
     Nodes_list.push_back(new Node(4,6,12));
     
    PJS PJS_obj(Nodes_list);
    CCU ccu_obj(Nodes_list,&PJS_obj);
    
    unsigned long long num_loops;
    if(argc < 2){
        num_loops= 10000;
    }
    else{
        std::istringstream ss(argv[1]);
        if(!(ss>>num_loops)){
            std::cerr<<"Invalid number"<< argv[1]<< std::endl;
        }
    }
    std::cout<<"Going to run for "<<num_loops<<" loops."<<std::endl;

    unsigned long long counter=0;
    while(counter<num_loops && !(PJS_obj.outOfJobs() && stats.getCoresUSed()==0)){
        //Do things here
       //Reset the statistics
        stats.setCoresUSed(0);
        stats.settotalCores(0);
        stats.setGBUSed(0);
        stats.settotalGB(0);
        if(!PJS_obj.outOfJobs() && counter%JOB_GENERATOR_TIME==0){
            //Read in jobs from a file and obtain the tasks into the current batch
            PJS_obj.RecieveJobs();
        }
        if(counter%PJS_SCHEDULING_TIME==0){
            //Have PJS send jobs to Nodes.
            
            PJS_obj.CheckForTasks();
               PJS_obj.Start_PJS(Nodes_list);
        }
        
        if(counter%NODE_SCHEDULER_TIME == 0){
            for(std::vector<Node*>::iterator it= Nodes_list.begin(); it!=Nodes_list.end(); it++){
                (*it)->Scheduler();
            }
        }
        if(counter%NODE_EXECUTOR_TIME == 0){
            for(std::vector<Node*>::iterator it = Nodes_list.begin(); it != Nodes_list.end(); it++){
                //Insert executor code.
                (*it)->Execute();
            }
        }
        if(counter%NODE_MATRIX_SEND_TIME==0){
            for(std::vector<Node*>::iterator it= Nodes_list.begin(); it!=Nodes_list.end(); it++){
                (*it)->Create_Waittime_matrix();
                (*it)->SendMatrix();
            }
        }
        if(counter%CCU_UPDATE_TIME==0){
            //Check for matricies to update CCU
            ccu_obj.update_matrix();
            ;
        }
        
        //increment clock
        counter++;
        //collect stats
        stats.incClock();
        //Record the statistics;
        stats.recordMemoryUtilization();
        stats.recordCpuUtilization();
    }
    return 0;
}

