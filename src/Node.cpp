#include "Node.h"

inline void threadsafe_msg(std::string s){
    output_mutex.lock();
    std::cout<<s<<std::endl;
    output_mutex.unlock();
}
template<typename T>
inline void threadsafe_msg(std::string s, T val){
    output_mutex.lock();
    std::cout<<s<<val<<std::endl;
    output_mutex.unlock();
}

Node::Node(int _id,int num_cores): id(_id), CORESNUM(num_cores),
        pjsNodecv(new std::condition_variable),PJSNode(pjsNodecv) 
{
    threadsafe_msg("Node constructor id = ",_id);   
    node_thread_ptr = std::unique_ptr<std::thread>(new std::thread(&Node::Start_Node,this));        
}

Node::Node(const Node& orig) : id(orig.getId()), 
        CORESNUM(orig.getCoreNum()),pjsNodecv(new std::condition_variable),
        PJSNode(pjsNodecv) 
{
    threadsafe_msg("Node constructor id = ",orig.getId());   
    node_thread_ptr = std::unique_ptr<std::thread>(new std::thread(&Node::Start_Node,this));   
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
     threadsafe_msg("This is scheduler");
    //    while(true)
    {
      while(!queue.empty()) 
        addTask(PJSNode.getTask());
    }
}

void Node::CreateExecuters(){
 
    threadsafe_msg("Creating Executers");
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

/*******************************************************************************
 ************************CPU FUNCTIONS******************************************
 ******************************************************************************/

CPU::CPU(Node* ptr){
       
    executor_thread_ptr = std::unique_ptr<std::thread>(new std::thread(&CPU::Executer,this));
    //std::cout<<"CPU constructor" <<ptr->getId()<<std::endl;
    threadsafe_msg("CPU constructor");
    //threadsafe_msg(ptr->getId());
    
}

CPU::CPU(const CPU& orig){
}

CPU::~CPU(){
    executor_thread_ptr->join();
}

void CPU::Executer( ){
   // Task t = getTask();
    threadsafe_msg("This is executer");
}
