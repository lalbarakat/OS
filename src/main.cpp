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
    NODE_MATRIX_SEND_TIME=1,
    NODE_EXECUTOR_TIME=1,
    PJS_SCHEDULING_TIME=1,
    JOB_GENERATOR_TIME=50
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
    int num_nodes = 20;
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
    for(int i=0; i< num_nodes; ++i){
     Nodes_list.push_back(new Node(i,8,26));
    }
    PJS PJS_obj(Nodes_list);
    CCU ccu_obj(Nodes_list,&PJS_obj);
    
    unsigned long long num_loops;
    if(argc < 2){
        num_loops= ULLONG_MAX;
    }
    else{
        std::istringstream ss(argv[1]);
        if(!(ss>>num_loops)){
            std::cerr<<"Invalid number"<< argv[1]<< std::endl;
        }
    }
    std::cout<<"Going to run for "<<num_loops<<" loops."<<std::endl;
    
    
    int num_jobs=3;
    int idle_counter=0;
    unsigned long long counter=0;
    while(counter<num_loops && !(PJS_obj.outOfJobs() && idle_counter>30)){
        //Do things here
       //Reset the statistics
        stats.setCoresUSed(0);
        stats.settotalCores(0);
        stats.setGBUSed(0);
        stats.settotalGB(0);
        stats.setQueueSize(0);
        if(!PJS_obj.outOfJobs() && counter%JOB_GENERATOR_TIME==0){
          //Read in jobs from a file and obtain the tasks into the current batch
            PJS_obj.RecieveJobs(num_jobs);
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
                (*it)->sendCache();
            }
        }
        if(counter%NODE_MATRIX_SEND_TIME==0){
            //Check for matricies to update CCU
            ccu_obj.update_matrix();
            ccu_obj.update_Global_cache();
        }
        if(counter%100==0){
            if(num_jobs==15)
                num_jobs=3;
            else
                num_jobs+=3;
        }
        //increment clock
        counter++;
        //collect stats
        stats.incClock();
        //Record the statistics;
        stats.recordMemoryUtilization();
        stats.recordCpuUtilization();
        if(stats.getCoresUSed()==0){
            idle_counter++;
        }
        else{
            idle_counter=0;
        }
    }
    return 0;
}


