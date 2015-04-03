//#include <c++/4.6/iostream>

#include "Node.h"
//#include "Task.h"


Node::Node(int _id,int num_cores) {
    std::cout<<"Node constructor id = "<< _id<<std::endl;
    id = _id;
    CORESNUM = num_cores;
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
//    while(true)
    {
      while(!queue.empty()) 
        addTask(PJSNode.getTask());
    }
}

void Node::CreateExecuters(){
    std::cout<<"hello";    
    for (int i = 0; i < CORESNUM; i++){
        CPU *c = new CPU(this);
    }
}
void Node::addTask(Task t){
    qmutex.lock();
    queue.push(t);
    qmutex.unlock();
}

Task Node::getTask(){
    qmutex.lock();
    Task t= queue.front();
    queue.pop();
    qmutex.unlock();
    return t;
}
//void Node::SumbitTask(Task t)
//void Node::SumbitTask() {
//    int num= 100;
//    for (int i=0;i<num; i++){
//       // Task *tmp = new Task(i, std::rand(), std::rand()%2048);
//        Task *tmp = new Task(i,i,i);
//        QTasks.push_back(*tmp);
//    }
//    std::cout<<QTasks.size()<<std::endl;
//}
//
//
//void Node::PrintQ() {
//    /*
//    for(int i=0; i<QTasks.size();i++) {
////        std::cout<<"Taskid = " + std::to_string(QTasks[i].getTask_id());
////        std::cout<<"\tCPU = " + std::to_string(QTasks[i].getCPU_time());
////        std::cout<<"\tMemory = "+ std::to_string(QTasks[i].getMemory_required())<<std::endl;
//        
//        std::cout<<"Taskid = " + std::to_string(QTasks[i].getTask_id()) + 
//                "\tCPU = " + std::to_string(QTasks[i].getCPU_time()) + 
//                "\tMemory = "+ std::to_string(QTasks[i].getMemory_required())
//                <<std::endl;
//    }*/
//}

/*******************************************************************************
 ************************CPU FUNCTIONS******************************************
 ******************************************************************************/

CPU::CPU(Node* ptr){
//    int id = _id;
    std::cout<<"CPU constructor" <<ptr->getId()<<std::endl;
    std::thread ex (&CPU::Executer, this);
    ex.join();
    
}

CPU::CPU(const CPU& orig){
}

CPU::~CPU(){
}

void CPU::Executer(){
   // Task t = getTask();
    std::cout<<"This is executer"<<std::endl;
}