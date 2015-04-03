#include <cstdlib>
#include "Node.h"
#include "Task.h"
#include "PJS.h"
#include "CCU.h"

using namespace std;
std::mutex output_mutex;

/*
 * 
 */
std::vector<Node *> Nodes_list;
 void create_nodes(int id) {
     std::cout<<"Node # " << id <<std::endl;
     Node *n =new Node(id,4);
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
    std::thread t[num_nodes];
    std::thread ccu_thread;
    std::thread PJS_thread;
    //Launch a group of threads
    for (int i = 0; i < num_nodes; ++i) {
        t[i] = std::thread(create_nodes, i);
    }
    ccu_thread = std::thread(create_ccu);
    PJS_thread = std::thread(create_PJS);
    
    
    output_mutex.lock();
    std::cout<<"Main thread still here"<<std::endl;
    output_mutex.unlock();
    
    std::this_thread::sleep_for(std::chrono::seconds(1));

    //Join the threads with the main thread
    PJS_thread.join();
    ccu_thread.join();    
    for (int i = 0; i < num_nodes; ++i) {
        t[i].join();
    }
      
   // Node *n = new Node(1);
    
    return 0;
}

