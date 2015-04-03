//#include <c++/4.6/iostream>

#include "Node.h"
#include "Task.h"


Node::Node(int _id,int num_cores) {
    std::cout<<"Node constructor id = "<< _id<<std::endl;
    id = _id;
    CORESNUM = num_cores;
    node_thread_ptr = std::unique_ptr<std::thread>(new std::thread(&Node::Start_Node,this));        
}

Node::Node(const Node& orig) {
}

Node::~Node() {
    scheduler_thread_ptr->join();
    node_thread_ptr->join();
    //Destroy the CPU Objects
    for (std::vector<CPU *>::iterator it = CPU_ptr_list.begin() ; it != CPU_ptr_list.end(); ++it)
    {
        delete (*it);
    }
    
    
}
//Start node creates Scheduler, Executors and other operations such as creation of wait time matrices, sending them to CCU, PJS etc.
void Node::Start_Node(){
    scheduler_thread_ptr = std::unique_ptr<std::thread>(new std::thread(&Node::Scheduler,this));
    CreateExecuters();   
    Create_Waittime_matrix();

    }

void Node::Create_Waittime_matrix(){

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
 
    for (int i = 0; i < CORESNUM; i++){
        CPU_ptr_list.push_back(new CPU(this));
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
       
    executor_thread_ptr = std::unique_ptr<std::thread>(new std::thread(&CPU::Executer,this));
    std::cout<<"CPU constructor" <<ptr->getId()<<std::endl;
    
}

CPU::CPU(const CPU& orig){
}

CPU::~CPU(){
    executor_thread_ptr->join();
}

void CPU::Executer( ){
   // Task t = getTask();
    std::cout<<"This is executer"<<std::endl;
}