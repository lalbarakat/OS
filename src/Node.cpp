#include "Node.h"
//#include "Task.h"


//Node::Node() {
//}

//Node::Node(const Node& orig) {
//}

//Node::~Node() {
//}

//void Node::Scheduler(){
//   
//}

//void Node::SumbitTask(Task t)
void Node::SumbitTask() {
    int num= 100;
    for (int i=0;i<num; i++){
       // Task *tmp = new Task(i, std::rand(), std::rand()%2048);
        Task *tmp = new Task(i,i,i);
        QTasks.push_back(*tmp);
    }
    
    std::cout<<QTasks.size()<<std::endl;
}

void Node::PrintQ() {
    /*
    for(int i=0; i<QTasks.size();i++) {
//        std::cout<<"Taskid = " + std::to_string(QTasks[i].getTask_id());
//        std::cout<<"\tCPU = " + std::to_string(QTasks[i].getCPU_time());
//        std::cout<<"\tMemory = "+ std::to_string(QTasks[i].getMemory_required())<<std::endl;
        
        std::cout<<"Taskid = " + std::to_string(QTasks[i].getTask_id()) + 
                "\tCPU = " + std::to_string(QTasks[i].getCPU_time()) + 
                "\tMemory = "+ std::to_string(QTasks[i].getMemory_required())
                <<std::endl;
    }*/
}

