#include <cstdlib>
#include <chrono>
#include "Node.h"
#include "Task.h"
#include "PJS.h"
#include "CCU.h"

using namespace std;

/*
 * 
 */
std::vector<Node *> Nodes_list;
 void create_nodes(int id,int num_cores) {
     std::cout<<"Node # " << id <<std::endl;
     Node *n =new Node(id,num_cores);
     //adding to the list of nodes.
     Nodes_list.push_back(n);
    }
 
 void create_ccu() {
     std::cout<<"CCU thread created " <<std::endl;
     
    }
  
 void create_PJS() {
     std::cout<<"PJS thread created " <<std::endl;
     PJS *PJS_obj = new PJS(Nodes_list);
    }
 
int main(int argc, char** argv) {
    int num_nodes = 5;
    for (int i = 0; i < num_nodes; ++i) {
        create_nodes(i,1+i);
    }
    
    create_PJS(); 
    output_mutex.lock();
    std::cout<<"Main thread still here"<<std::endl;
    output_mutex.unlock();
    std::this_thread::sleep_for(std::chrono::seconds(20));
    return 0;
}

