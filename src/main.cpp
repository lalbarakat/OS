#include <cstdlib>
#include "Node.h"
#include "Task.h"

using namespace std;
std::mutex output_mutex;

/*
 * 
 */

 void create_nodes(int id) {
     std::cout<<"Node # " << id <<std::endl;
     Node *n =new Node(id);
    }
int main(int argc, char** argv) {
    int num_nodes = 2;
    std::thread t[num_nodes];

    //Launch a group of threads
    for (int i = 0; i < num_nodes; ++i) {
        t[i] = std::thread(create_nodes, i);
    }
    
    output_mutex.lock();
    std::cout<<"Main thread still here"<<std::endl;
    output_mutex.unlock();
    
    std::this_thread::sleep_for(std::chrono::seconds(1));

    //Join the threads with the main thread
    for (int i = 0; i < num_nodes; ++i) {
        t[i].join();
    }
    
   // Node *n = new Node(1);
    
    return 0;
}

