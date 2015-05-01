#include "Node.h"
#include <chrono>
#include <ctime>
using namespace std;
Node_CCU Node::NodeCCU;
CCU_Node Node::CCUNode;

Node::Node(int _id,int num_cores,int memory): id(_id), CORESNUM(num_cores),MAINMEMORY(memory)
{
   std::cout<<"Node constructor id = "<<_id<<std::endl;   
   resize(local_wait_time_matrix,4,4,-1);//Initialize wait time matrix
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
    for (std::deque<Task>::iterator it = regularQueue.begin(); it!=regularQueue.end(); ++it)
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
    //std::cout<<"This is scheduler"<<std::endl;
    
    while(!PJSNode.isEmpty())
    {
        Task t=PJSNode.getTask();
        //std::cout<<"Task from PJS_Node"<<t.getTaskId()<<std::endl;
        //std::cout<<"Task from PJS_Node"<<t.getCores_required()<<std::endl;
        if(!(t.getTaskMode()))//0 for regular mode task
            addRegularTask(t);
        else// //1 for oppurtunistic
            addOppurtunisticTask(t);
    }
    //std::cout<<"Task id"<<id<<t.getTaskId()<<std::endl;
    //std::cout<<"Task exec time"<<id<<t.getCPU_time()<<std::endl;
    //std::cout<<"Task memory"<<id<<t.getMemory_required()<<std::endl;
}

void Node::Execute(){
    CPU_ptr_list[0]->Executer(this);
}

void Node::CreateExecuters(){
 
    std::cout<<"Creating Executers"<<std::endl;
    CPU_ptr_list.push_back(new CPU(this));
}

void Node::Create_Waittime_matrix(){
    
/*    Task *t1= new Task(0,1,40,4,2);
    
    regularQueue.push_back(*t1);
    Task *t2= new Task(0,1,10,2,2);
    
    regularQueue.push_back(*t2);
    Task *t3= new Task(0,1,30,4,2);
    
    regularQueue.push_back(*t3);
    Task *t4= new Task(0,1,20,2,4);*/
    //queue.push_back(*t4);    
    resize(local_wait_time_matrix,4,4,-1);
    
    for (size_t i=0; i<local_wait_time_matrix.size(); i++) 
    {
        for (size_t j=0; j<local_wait_time_matrix.size(); j++) 
        {
            Task *t = new Task(0,5,0,Mem_array[j],cores_array[i],1);
            addRegularTask(*t);
            if(cores_array[i] > CORESNUM || Mem_array[j] > MAINMEMORY)
                local_wait_time_matrix[i][j] = -1;
            else
                local_wait_time_matrix[i][j] = Estimatewaittime(cores_array[i],Mem_array[j]);           
            getRegularTaskfromback();
            delete t;
        }
    }
}


Task* Node::getRegularTask(){
    Task *t = NULL;
    if(regularQueue.empty())
    {
        t=NULL;
        return NULL;
    }
    t= &(regularQueue.front());
    regularQueue.pop_front();
    return t;
}

Task* Node::getRegularTaskfromback()
{
    Task *t = NULL;
    if(regularQueue.empty())
    {
        t=NULL;
        return NULL;
    }
    t= &(regularQueue.back());
    regularQueue.pop_back();
    return t;
}

Task* Node::PeekRegularTask(){
    
    if(regularQueue.empty())
    {    
        return NULL;
    }
    return &(regularQueue.front());
    
}


void Node::addRegularTask(Task t){
    regularQueue.push_back(t);
}

Task* Node::getOppurtunisticTask(){
    Task *t = NULL;
    if(OppurtunisticQueue.empty())
    {
        return NULL;
    }
    t= &(OppurtunisticQueue.front());
    OppurtunisticQueue.pop_front();
    return t;
}

Task* Node::PeekOppurtunisticTask(){
    if(OppurtunisticQueue.empty())
    {
       return NULL;
    }
    return &(OppurtunisticQueue.front());    
}


void Node::addOppurtunisticTask(Task t){
    OppurtunisticQueue.push_back(t);
}


void Node::addOppurtunisticTasktofront(Task t){
    OppurtunisticQueue.push_front(t);
}

void Node::sendCache()
{
    CPU_ptr_list[0]->sendCache(this);
}

/*******************************************************************************
 ************************CPU FUNCTIONS******************************************
 ******************************************************************************/

CPU::CPU(Node* ptr){
       
    node_ptr = ptr;
    std::cout<<"CPU constructor"<<std::endl; 
    Cores.reserve(ptr->CORESNUM);
    Memory.reserve(ptr->MAINMEMORY);
    for(int i =0;i<ptr->CORESNUM;i++)
        Cores[i].second = 0;
    for(int i=0;i<ptr->MAINMEMORY;i++)
        Memory[i].second = 0;
    }

CPU::CPU(const CPU& orig){
}

CPU::~CPU(){
}


int CPU::numberoffreecores(int coresnum,bool isRegular)
{
    int freecores = 0;
    for(int i = 0;i<coresnum;i++)
    {
        if((Cores[i].second<=0 || (isRegular && Cores[i].first.getTaskMode())))
            freecores++;
    }
    //stats.inctotalCores();
    return freecores;
}

int CPU::numberoffreememory(int mainmemory,bool isRegular)
{
    int freememory = 0;
    for(int i = 0;i<mainmemory;i++)
    {
        if((Memory[i].second<=0 || (isRegular && Memory[i].first.getTaskMode())))
            freememory++;
    }
  //  stats.inctotalGB();
    return freememory;
}

void CPU::RecordNumberOfUsedCores(int coresnum)
{
    
    for(int i = 0;i<coresnum;i++)
    {
        if(!(Cores[i].second<=0))           
        {
            stats.incCoresUSed();
            //increasing the cores used to track CPU Utilization
        }
    }   
    
}

void CPU::RecordNumberOfUsedGB(int mainmemory)
{
    
    for(int i = 0;i<mainmemory;i++)
    {
        if(!(Memory[i].second<=0))           
        {
            stats.incGBUSed();
            //increasing the cores used to track CPU Utilization
        }
    }
    stats.incGBUSed(local_cache.size()*2);
    
}


void CPU::printtologfile(Node *ptr,Task t,time_t now)
{
    char* dt = ctime(&now);
    
    std::cout<<"Task id "<<t.getTaskId()<<" of Job id "<<t.getJob_id()<<" started executing at node "<<ptr->getId()<<" consuming "<<t.getCores_required()<<" Cores "
            " and " <<t.getMemory_required()<<"  GB amount of memory at time "<<dt<<" for time "<<t.getCPU_time()<<" seconds and size = "<<local_cache.size()<<std::endl;
}

void CPU::Zerointhearrays(Task preempted_task,Node *ptr)
{
    for(int j=0;j<ptr->MAINMEMORY;j++)//zero in all the preempted oppurtunistic task's time in both the arrays.
    {
        if(Memory[j].first.getTaskId() == preempted_task.getTaskId())
        Memory[j].second = 0;
    }
    for(int j=0;j<ptr->CORESNUM;j++)//zero in all the preempted oppurtunistic task's time in both the arrays.
    {
        if(Cores[j].first.getTaskId() == preempted_task.getTaskId())
        Cores[j].second = 0;
    }
}

void CPU::validate(int coresnum,int mainmemory)
{
    for(int i=0;i<coresnum;i++)
    {
        if(Cores[i].second>0){
            Cores[i].second--;
            if(Cores[i].second==0){
                bool isFirst=true;
                for(int j=i-1; j>=0;j--){
                    if(Cores[j].first.getJob_id()==Cores[i].first.getJob_id() &&
                            Cores[j].first.getTaskId()==Cores[i].first.getTaskId()){
                        
                        isFirst=false;
                        break;
                    }
                }
                if(isFirst)
                {         
                    NodePJS_queue.push(Cores[i].first);
                    stats.recordCompletedTask(Cores[i].first.getJob_id(),Cores[i].first.getTaskId());
                }
            }
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


bool CPU::IsScheduled(Task t,Node *ptr,int coresnum,int mainmemory,bool isRegular)
{
    time_t now = time(0);
    int num_cores=numberoffreecores(coresnum,isRegular);
    int num_mem = numberoffreememory(mainmemory, isRegular);
   if( num_cores  >= t.getCores_required() && num_mem >= t.getMemory_required())
   {
       //Task is scheduled
       Block b = t.get_block();
       
       //Use Global Cache from CCU to write cache eviction policy
        GlobalCache global_cache;
        if(!ptr->CCUNode.isCacheEmpty())
        {
            global_cache = ptr->CCUNode.getGlobalCache();
        }
       //check if block of that task is in cache?
       if(!IsPresentInCache(b))
       {
           //wait for 20 seconds before start executing the task
           addToCache(b,ptr,global_cache);
           t.setCPU_time(t.getCPU_time()+20);
       }
       else//If block is present in cache. Then Update the time stamp for LRU
       {
           UpdateCache(b,global_cache);
       }
       
       int reqdcores = 0;
       for(int i =0;i<ptr->CORESNUM;i++)
       {
           if(Cores[i].second ==0 && reqdcores < t.getCores_required())
           {
               
               Cores[i].second = t.getCPU_time();
               Cores[i].first = t;
               reqdcores++;
           }
           else if(Cores[i].second!=0 && isRegular && Cores[i].first.getTaskMode() && (reqdcores < t.getCores_required()))
            {
                    Cores[i].first.setCPU_time(Cores[i].second);
                    ptr->addOppurtunisticTasktofront(Cores[i].first);
                    //preempt the oppurtunistic task and put it back in the oppurtinistic queue.
                    Zerointhearrays(Cores[i].first,ptr);
                    Cores[i].second = t.getCPU_time();
                    Cores[i].first = t;
                    reqdcores++;
            }
       }
       
       int reqdMemory = 0;
       for(int i =0;i<ptr->MAINMEMORY;i++)
       {
           if(Memory[i].second ==0 && reqdMemory < t.getMemory_required())
           {
               
               Memory[i].second = t.getCPU_time();
               Memory[i].first = t;
               reqdMemory++;
           }
           else if(Memory[i].second!=0 && isRegular && Memory[i].first.getTaskMode() && (reqdMemory < t.getMemory_required()))
            {
                    Memory[i].first.setCPU_time(Memory[i].second);
                    ptr->addOppurtunisticTasktofront(Memory[i].first);
                    //preempt the oppurtunistic task and put it back in the oppurtinistic queue.
                    Zerointhearrays(Memory[i].first,ptr);
                    Memory[i].second = t.getCPU_time();
                    Memory[i].first = t;
                    reqdMemory++;
            }
       }
     
      // printtologfile(ptr,t,now);
       
       return true;
   }
   else
      return false;
   }

void CPU::Executer(Node *ptr ){
    
        Task *t = NULL;
            
        
            t= ptr->PeekRegularTask();
            while(!(ptr->regularQueue.empty()) && IsScheduled(*t,ptr,ptr->CORESNUM,ptr->MAINMEMORY,1))
            {                        
                   ptr->getRegularTask();
                   t = ptr->PeekRegularTask();
            }

            std::sort(Cores.begin(),Cores.end(),Xgreater());
            std::sort(Memory.begin(),Memory.end(),Xgreater());
            //Oppurtunistic Scheduling
              t = ptr->PeekOppurtunisticTask();
             while(!(ptr->OppurtunisticQueue.empty()) && IsScheduled(*t,ptr,ptr->CORESNUM,ptr->MAINMEMORY,0))
             {
                      ptr->getOppurtunisticTask();
                  t = ptr->PeekOppurtunisticTask();
             }

            validate(ptr->CORESNUM,ptr->MAINMEMORY);
//            std::cout<<"This is executer"<<std::endl;    
            stats.inctotalCores(ptr->CORESNUM);
            stats.inctotalGB(ptr->MAINMEMORY);
            stats.incQueueSize(ptr->regularQueue.size());
            RecordNumberOfUsedCores(ptr->CORESNUM);
            RecordNumberOfUsedGB(ptr->MAINMEMORY);              
            //print the local_cache
            
}



bool CPU::IsPresentInCache(Block b)
{
    for(int i =0;i< local_cache.size();i++)
    {
      if(local_cache[i].first.get_block_id() == b.get_block_id() && local_cache[i].first.get_file_id() == b.get_file_id())   
          return true;
    }
    return false;
}

void CPU::addToCache(Block b,Node *ptr,GlobalCache global_cache)
{
    int clk;
    clk = stats.getClock();
    
    set_cachesize(5);
    
    //check if the cache is full.
    if(local_cache.size()< get_cachesize())//If not full
    {
        
        local_cache.push_back(std::make_pair(b,clk));
        
        /*cout<<"Node id "<<ptr->getId()<<endl;
            for(int i =0; i<local_cache.size();i++)
            {
                cout<<local_cache[i].first.get_block_id()<<"  "<<local_cache[i].first.get_file_id()<<" "<<local_cache[i].second<<endl;
            }
        */
    }
    else //Cache is full. Find a block to Replace - Implement LRU
    {
        int min_clock = stats.getClock()+1;
        int min_cache = local_cache.size();
        for(int i =0;i<local_cache.size();i++)
        {
            if(local_cache[i].second < min_clock)
            {
                min_clock = local_cache[i].second;
                min_cache = i;
            }            
        }
        if(min_cache<local_cache.size())
        {
            local_cache[min_cache].first = b;
            local_cache[min_cache].second = stats.getClock();
        }
        
      /*cout<<"Node id "<<ptr->getId()<<endl;
            for(int i =0; i<local_cache.size();i++)
            {
                cout<<local_cache[i].first.get_block_id()<<"  "<<local_cache[i].first.get_file_id()<<" "<<local_cache[i].second<<endl;
            }*/
    }
        
}

    void deleteFromCache(Block b){}
    
    void CPU::UpdateCache(Block b,GlobalCache global_cache)
    {
        for(int i =0;i<local_cache.size();i++)
        {
            if(local_cache[i].first.get_block_id() == b.get_block_id() && local_cache[i].first.get_file_id() == b.get_file_id())
            {
                local_cache[i].second = stats.getClock();
                return;
            }
        }
    }

    void CPU::sendCache(Node *ptr)
    {
        ptr->NodeCCU.addToCache(std::make_pair(ptr->getId(),local_cache));
    }
