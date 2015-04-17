#include "Node.h"
#include <chrono>
#include <ctime>

Node_CCU Node::NodeCCU;

Node::Node(int _id,int num_cores,int memory): id(_id), CORESNUM(num_cores),MAINMEMORY(memory)
{
    std::cout<<"Node constructor id = "<<_id<<std::endl;   
    CreateExecuters();          
}

Node::Node(const Node& orig) : id(orig.getId()), CORESNUM(orig.getCoreNum()), MAINMEMORY(orig.getMemory())
{
    std::cout<<"Node constructor id = "<<orig.getId()<<std::endl;   
    CreateExecuters();   
}

Node::~Node() {
    for (std::vector<CPU *>::iterator it = CPU_ptr_list.begin() ; it != CPU_ptr_list.end(); ++it)
    {
        delete (*it);
    }
       
}

void Node::SendMatrix(){
    NodeCCU.addWaitTimeMatrix(id, local_wait_time_matrix);
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
     
    /* for(int i =0 ;i<CORESNUM;i++)
     cout<<Cores[i]<<" ";
     cout<<endl<<endl;
    for(int i =0 ;i<MAINMEMORY;i++)
     cout<<Memory[i]<<" ";
     cout<<endl<<endl;*/
     if(min_memory > min_core) return min_memory;
     else return min_core;
 }

float Node::Estimatewaittime(int cores, int memory)
{
 int Cores[CORESNUM]={0};
 int Memory[MAINMEMORY]={0};
 int min_val=0;
    for (std::deque<Task>::iterator it = queue.begin(); it!=queue.end(); ++it)
    {
        Task task = *it;
        min_val = FindMinVal(Cores,Memory,CORESNUM,MAINMEMORY,task.getCores_required(),task.getMemory_required());
        
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
// cout<<"\n\n\n;";
 
 return Node::FindMinVal(Cores,Memory,CORESNUM,MAINMEMORY,cores,memory);
        
 }

void Node::Scheduler(){
    std::cout<<"This is scheduler"<<std::endl;
    Task t=PJSNode.PeekTask();
    std::cout<<"Task from PJS_Node"<<t.getTaskId()<<std::endl;
    std::cout<<"Task from PJS_Node"<<t.getCores_required()<<std::endl;
    addTask(PJSNode.getTask());
    std::cout<<"Task id"<<id<<t.getTaskId()<<std::endl;
    std::cout<<"Task exec time"<<id<<t.getCPU_time()<<std::endl;
    std::cout<<"Task memory"<<id<<t.getMemory_required()<<std::endl;
}

void Node::Execute(){
    CPU_ptr_list[0]->Executer(this);
}

void Node::CreateExecuters(){
 
    std::cout<<"Creating Executers"<<std::endl;
    CPU_ptr_list.push_back(new CPU(this));
}

void Node::addTask(Task t){
    queue.push_back(t);
}

void Node::Create_Waittime_matrix(){
    Task *t1= new Task(0,1,40,4,2);
    
    queue.push_back(*t1);
    Task *t2= new Task(0,1,10,2,2);
    
    queue.push_back(*t2);
    Task *t3= new Task(0,1,30,4,2);
    
    queue.push_back(*t3);
    Task *t4= new Task(0,1,20,2,4);
    //queue.push_back(*t4);    
    resize(local_wait_time_matrix,4,4,-1);
    
    for (size_t i=0; i<local_wait_time_matrix.size(); i++) 
    {
        for (size_t j=0; j<local_wait_time_matrix.size(); j++) 
        {
            Task *t = new Task(0,5,0,Mem_array[j],cores_array[i]);
            addTask(*t);
            if(cores_array[i] > CORESNUM || Mem_array[j] > MAINMEMORY)
                local_wait_time_matrix[i][j] = -1;
            else
                local_wait_time_matrix[i][j] = Estimatewaittime(cores_array[i],Mem_array[j]);
            getTask();
            delete t;
        }
    }
}

Task Node::getTask(){
    Task t= queue.front();
    queue.pop_front();
    return t;
}

Task Node::PeekTask(){
    return queue.front();
}

/*******************************************************************************
 ************************CPU FUNCTIONS******************************************
 ******************************************************************************/

CPU::CPU(Node* ptr){
       
    node_ptr = ptr;
    std::cout<<"CPU constructor"<<std::endl; 
    Cores.reserve(ptr->CORESNUM);
    Memory.reserve(ptr->MAINMEMORY);
    }

CPU::CPU(const CPU& orig){
}

CPU::~CPU(){
}


void CPU::validate(int coresnum,int mainmemory)
{
    for(int i=0;i<coresnum;i++)
    {
        if(Cores[i].second>0)
            Cores[i].second--;
        if(Cores[i].second==0)
        {         
            NodePJS_queue.push(Cores[i].first);
            stats.recordCompletedTask(Cores[i].first.getJob_id(),Cores[i].first.getTaskId());
        }
    }
    
    for(int i=0;i<mainmemory;i++)
    {      
        if(Memory[i].second>0)
            Memory[i].second--;       
    }
    
    std::sort(Cores.begin(),Cores.end(),Xgreater());
    std::sort(Memory.begin(),Memory.end(),Xgreater());
}


int CPU::numberoffreecores(int coresnum)
{
    int freecores = 0;
    for(int i = 0;i<coresnum;i++)
    {
        if(Cores[i].second==0)
            freecores++;
        else
        {
            stats.incCoresUSed();
            //increasing the cores used to track CPU Utilization
        }
    }
    stats.inctotalCores();
    return freecores;
}

int CPU::numberoffreememory(int mainmemory)
{
    int freememory = 0;
    for(int i = 0;i<mainmemory;i++)
    {
        if(Memory[i].second==0)
            freememory++;
        else
        {
            stats.incGBUSed();
        }
    }
    stats.inctotalGB();
    return freememory;
}

void CPU::printtologfile(Task t,time_t now)
{
    char* dt = ctime(&now);
    std::cout<<"Task "<<t.getTaskId()<<"started executing at Node "<<node_ptr->getId()<<" consuming "<<t.getCores_required()<<" Cores "
            "and " <<t.getMemory_required()<<"  GB amount of memory at time "<<dt<<" for time "<<t.getCPU_time()<<" seconds"<<std::endl;
}

bool CPU::IsScheduled(Task t,int coresnum,int mainmemory)
{
    time_t now = time(0);
    
   if( numberoffreecores(coresnum) >= t.getCores_required() && numberoffreememory(mainmemory) >= t.getMemory_required())
   {
       for(int i=0;i<t.getCores_required();i++)
       {
           Cores[i].second = t.getCPU_time();
           Cores[i].first = t;
       }
       for(int i=0;i<t.getMemory_required();i++)
       {
           Memory[i].second = t.getCPU_time();
           Memory[i].first = t;
       }
       printtologfile(t,now);
       return true;
   }
   else
   {
       return false;
   }
}


void CPU::Executer(Node *ptr ){
   // Task t = getTask();
    
    
    /*while(!(ptr->queue.empty()))
    {
        Task t = ptr->PeekTask();
        
        if(IsScheduled(t,ptr->CORESNUM,ptr->MAINMEMORY))
        {
            ptr->getTask();
        }
    }
    
    validate(ptr->CORESNUM,ptr->MAINMEMORY);
    */
     Task t = ptr->PeekTask();
    while(!(ptr->queue.empty()) && IsScheduled(t,ptr->CORESNUM,ptr->MAINMEMORY))
    {                        
            ptr->getTask();
            t = ptr->PeekTask();
    }
    
    validate(ptr->CORESNUM,ptr->MAINMEMORY);
    
    std::cout<<"This is executer"<<std::endl;    
    
}
