#include "Node.h"
//#include "Task.h"


Node::Node(int _id) {
    id = _id;
    std::thread ts (&Node::Scheduler, this);
    ts.join();
    std::thread tx (&Node::CreateExecuters, this);
    tx.join();
}

Node::Node(const Node& orig) {
}

Node::~Node() {
}

void Node::Scheduler(){
    std::cout <<"This is scheduler"<<std::endl;
}

void Node::CreateExecuters(){
    std::cout<<id;
}
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

/*******************************************************************************
 ************************CPU FUNCTIONS******************************************
 ******************************************************************************/

CPU::CPU(int _id){
    int id = _id;
    int num = 4;
    std::thread t[num];
    for (int i = 0; i < num; ++i) {
      //  t[i] = std::thread(&CPU::Executer, this);
    }
    for (int i = 0; i < num; ++i) {
       // t[i].join();
    }
}

CPU::CPU(const CPU& orig){
}

CPU::~CPU(){
}
