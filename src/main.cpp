#include <cstdlib>
#include <chrono>
#include <thread>
#include <iostream>
#include "Node.h"
#include "Task.h"
#include "PJS.h"
#include "CCU.h"
bool running=true;

void waitForInput(){
    std::cin.get();
    running=false;
}

/*
 * 
 */
std::vector<Node *> Nodes_list;
 void create_node(int id,int num_cores) {
    std::cout<<"Node # " << id <<std::endl;
    Node *n =new Node(id,num_cores);
    //adding to the list of nodes.
    Nodes_list.push_back(n);
}
 
int main(int argc, char** argv) {
    int num_nodes = 5;
    for (int i = 0; i < num_nodes; ++i) {
        create_node(i,1+i);
    }
    PJS PJS_obj(Nodes_list);
    std::cout<<"Main thread still here"<<std::endl;
    CCU ccu_obj(Nodes_list);
    std::cout<<"Type any key to finish this program:"<<std::endl;
    std::thread t(waitForInput);
    
    while(running){
        //Do things here
        std::this_thread::yield();
        //increment counter
        //collect stats
    }
    t.join();
    return 0;
}

