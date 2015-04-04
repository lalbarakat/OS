#include "Node.h"
#include <chrono>
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
        condition_mutex(new std::mutex), pjsNodecv(new std::condition_variable),
        PJSNode(pjsNodecv, condition_mutex) 
{
    threadsafe_msg("Node constructor id = ",_id);   
    node_thread_ptr = std::unique_ptr<std::thread>(new std::thread(&Node::Start_Node,this));        
}

Node::Node(const Node& orig) : id(orig.getId()), 
        CORESNUM(orig.getCoreNum()),pjsNodecv(new std::condition_variable),
        condition_mutex(new std::mutex), PJSNode(pjsNodecv,condition_mutex) 
{
    threadsafe_msg("Node constructor id = ",orig.getId());   
    node_thread_ptr = std::unique_ptr<std::thread>(new std::thread(&Node::Start_Node,this));   
}

Node::~Node() {
    sched_running=false;
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
int Node::FindMinVal(int Cores[],int Memory[],int numofcores, int mainmemory,
        int task_cores,int task_mem)
 {
     int min_core,min_memory;
     int freqcores = 0;
     int freqmem = 0;
     std::sort(Cores,Cores+numofcores);
     std::sort(Memory,Memory+mainmemory);
     min_core = Cores[0];
     for(int i =0;i<numofcores;i++)
     {
        if(freqcores < task_cores) 
        {
            freqcores++;
            if(Cores[i]!=min_core)
            min_core = Cores[i];
        }
     }
     min_memory = Memory[0];
     for(int i =0;i<mainmemory;i++)
     {
        if(freqmem < task_mem) 
        {
            freqmem++;
            if(Memory[i]!=min_memory)
            min_memory = Memory[i];
        }
     }
     if(min_memory < min_core) return min_memory;
     else return min_core;
 }

float Node::Estimatewaittime(int cores, int memory)
{
 int available_memory = MAINMEMORY;
 int available_cores = CORESNUM;
 int waiting_time;
 int Cores[CORESNUM]={0};
 int Memory[MAINMEMORY]={0};
 int min_val=0;
    for (std::deque<Task>::iterator it = queue.begin(); it!=queue.end(); ++it)
    {
        Task task = *it;
        min_val = 
            Node::FindMinVal(Cores,Memory,CORESNUM,MAINMEMORY,
                task.getCores_required(),task.getMemory_required());
        
        int reqdcore = 0;
        int reqdmem = 0;
        for(int i = 0; i<CORESNUM;i++)
        {
            if(Cores[i]<=min_val && reqdcore<task.getCores_required())
            {
                Cores[i]=min_val+task.getCPU_time();
                reqdcore++;
            }
        }
        for(int i = 0; i<MAINMEMORY;i++)
        {
            if(Memory[i]<=min_val && reqdmem<task.getMemory_required())
            {
                Memory[i]=min_val+task.getCPU_time();
                reqdmem++;
            }
        }
    }
}
void Node::Scheduler(){
     threadsafe_msg("This is scheduler");
    while(sched_running)
    {
        std::unique_lock<std::mutex> lk(*condition_mutex);
        pjsNodecv->wait(lk,[this]{return PJSNode.isEmpty();} );
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
    queue.push_back(t);
    qmutex.unlock();
}
void Node::Create_Waittime_matrix(){
    Task *t1= new Task(1,30,2);
    t1->setCores_required(2);
    queue.push_back(*t1);
    Task *t2= new Task(1,30,2);
    t2->setCores_required(2);
    queue.push_back(*t2);
    Task *t3= new Task(1,30,2);
    t3->setCores_required(2);
    queue.push_back(*t3);
    Task *t4= new Task(1,30,2);
    t4->setCores_required(2);
    queue.push_back(*t4);    
    resize(local_wait_time_matrix,4,4,-1);
    for (int i=0; i<local_wait_time_matrix.size(); i++) 
    {
        for (int j=0; j<local_wait_time_matrix.size(); j++) 
        {
            local_wait_time_matrix[i][j] = Estimatewaittime(cores_array[i],Mem_array[j]);
        }
    }
}
Task Node::getTask(){
    qmutex.lock();
    Task t= queue.front();
    queue.pop_front();
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
