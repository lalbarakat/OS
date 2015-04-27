#include "PJS.h"
#include "Node.h"
#include "Task.h"
#include <set>

using namespace std;

PJS::PJS() : jobGen("jobs.txt"){
}

PJS::PJS(const PJS& orig): jobGen("jobs.txt") {
}

PJS::PJS(std::vector<Node *> Nodes_list): jobGen("jobs.txt") {
    //Start_PJS(Nodes_list);
}


Node* PJS::lookupnode(std::vector<Node *> Nodes_list,int min_node)
{
  for(std::vector<Node*>::iterator it = Nodes_list.begin();it!=Nodes_list.end();it++)    
  {
      if((*it)->getId() == min_node)
          return *it;
  }
  return NULL;
}

void PJS::stable_matcher(std::vector<Node *> Nodes_list,std::vector<Task>Task_list,std::vector<intMatPair> matpair) //matpair is the list of aggregated wait time matrices.
{
    
}

bool PJS::IsAlreadymatched(std::vector<int> matched_Nodes_list,int node_id)
{
    for(std::vector<int>::iterator it = matched_Nodes_list.begin(); it != matched_Nodes_list.end();it++)
    {
        if( (*it) == node_id)
            return true;
    }
    return false;
}
bool PJS::LookupBlockInGlobalCache(Task t, int node_id, Global_Cache global_cache)
{
    //check if tasks block is present in the node from globalcache
    for(int i =0;i<global_cache.size();i++)
    {
        if(global_cache[i].first.get_block_id() == t.get_block().get_block_id() && global_cache[i].first.get_file_id() == t.get_block().get_file_id())
        {
            std::list<int>::const_iterator iterator;
            for (iterator = global_cache[i].second.begin(); iterator != global_cache[i].second.end(); ++iterator) 
            {
                if(*iterator == node_id)
                    return true;
            }   
            
        }
    }
    return false;
}

std::vector<Task> PJS::Greedy_matcher(std::vector<Node *> Nodes_list,std::vector<Task>Task_list,std::vector<intMatPair> matpair,Global_Cache global_cache) //matpair is the list of aggregated wait time matrices.
{
    std::vector<int> matched_Nodes_list;
    std::vector<Task> unmatched_task_list(Task_list);
    int final_Estimate = 0;
    int Cache_Cost = 0;
    for(std::vector<Task>::iterator task_it = Task_list.begin();task_it!=Task_list.end();task_it++)
    {
        Task task = (*task_it);
        unsigned long min_time = 9999999;
        int min_node = 999999;
        for(std::vector<intMatPair>::iterator it=matpair.begin();it!=matpair.end();it++)
        {
         
            int id = (*it).first;//node id
            if(IsAlreadymatched(matched_Nodes_list,id))
            {
                continue;
            }
            if(LookupBlockInGlobalCache(task,id,global_cache))// Block is present in that node.
            {
                Cache_Cost = 0;
            }
            else//Block is not present in Cache. Need to add cost to transfer the files to that corresponding node
            {
                Cache_Cost = 20;
            }
            matrix_t waittime_matrix = (*it).second;//matrix  
            int req = task.getCores_required();
            int mem = task.getMemory_required();
            //Taking Memory Locality into account.
            final_Estimate = ((waittime_matrix[req%2][mem%4]!=-1)?waittime_matrix[req%2][mem%4] : 0 ) + Cache_Cost;
            if(final_Estimate < min_time )
            {
                   min_time = final_Estimate;
                   min_node = id;
            }
        }
        //Matching the task to the node
        Node *matched_node = lookupnode(Nodes_list,min_node);
        if(matched_node)
        {
            matched_node->PJSNode.addTask(task);
        //    cout<<" node matched "<<matched_node->getId()<<" with task "<<task.getTaskId()<<endl;
            matched_Nodes_list.push_back(min_node);
            //remove the matched task from unmatched_Task_list
            for( std::vector<Task>::iterator iter = unmatched_task_list.begin(); iter != unmatched_task_list.end(); ++iter )
            {
                if( (*iter).getTaskId() == task.getTaskId() )
                {
                    unmatched_task_list.erase( iter );
                    break;
                }
            }            
            
        }
    }
    return unmatched_task_list;
}

void PJS::Start_PJS(std::vector<Node *> Nodes_list)
{
    //Reading the aggregated wait time matrices from CCU_PJS
    AggregatedMatPair matpair;
    
    //Test code for Pacman. create sample of tasks
  
    if(stats.getClock() == 0)
    {
          curBatch.clear();
    Block b1(1,1);
    Task t1(1,0,30,2,2,1,b1);
    curBatch.push_back(t1);
    
    Block b2(2,1);
    Task t2(2,0,30,2,2,1,b2);
    curBatch.push_back(t2);
    
    Block b3(2,1);
    Task t3(3,0,30,2,2,1,b3);
    curBatch.push_back(t3);
    
    Block b4(3,1);
    Task t4(4,0,30,2,2,1,b4);
    curBatch.push_back(t4);
    
    Block b5(3,1);
    Task t5(5,0,30,2,2,1,b5);
    curBatch.push_back(t5);
    
    Block b6(4,1);
    Task t6(6,0,30,2,2,1,b6);
    curBatch.push_back(t6);
    
    Block b7(4,2);
    Task t7(7,0,30,2,2,1,b7);
    curBatch.push_back(t7);
    
    Block b8(1,2);
    Task t8(8,0,30,2,2,1,b8);
    curBatch.push_back(t8);
    
    Block b9(5,2);
    Task t9(9,0,30,2,2,1,b9);
    curBatch.push_back(t9);
    
    Block b10(1,3);
    Task t10(10,0,30,2,2,1,b10);
    curBatch.push_back(t10);
    
    Block b11(2,3);
    Task t11(11,0,30,2,2,1,b11);
    curBatch.push_back(t11);
    
    Block b12(3,3);
    Task t12(12,0,30,4,4,1,b12);
    curBatch.push_back(t12);
    
    Block b13(4,3);
    Task t13(13,0,30,4,4,1,b13);
    curBatch.push_back(t13);
    
    Block b14(5,3);
    Task t14(14,0,30,4,4,1,b14);
    curBatch.push_back(t14);
    
    Block b15(1,1);
    Task t15(15,0,30,4,4,1,b15);
    curBatch.push_back(t15);
    }
    //update
    Global_Cache global_cache;
    if(!(PJS::CCUPJS.isCacheEmpty()))
    {
         global_cache =CCUPJS.getGlobalCache();
        //print global_cache
   std::cout<<"aggregated cache"<<std::endl;
   for(int i = 0;i<global_cache.size();i++)
   {
       std::cout<<"Block block id "<<global_cache[i].first.get_block_id()<<" file id  "<<global_cache[i].first.get_file_id()<<" has Nodes ";
       std::list<int>::const_iterator iterator;
        for (iterator = global_cache[i].second.begin(); iterator != global_cache[i].second.end(); ++iterator) {
            std::cout << *iterator<<" ";
        }
       std::cout<<std::endl;
   }
    }
     for( std::vector<Task>::iterator iter = curBatch.begin(); iter != curBatch.end(); ++iter )
       {
             srand (time(NULL));
             int r = rand()%100;
             if(r>80)//2 in 10 are oppurtinsitic tasks. choosing them with 20% probability
               (*iter).SetTaskMode(1);//1 for oppurtunistic
             else
               (*iter).SetTaskMode(0);//0 for regular
       }
    if(!(PJS::CCUPJS.isMatrixEmpty()) && curBatch.size()>0)
    {
        matpair =  CCUPJS.PeekMatrix();
       //Randomly allocate tasks oppurtunistically.       
       std::vector<Task> unmatched_task_list = Greedy_matcher(Nodes_list,curBatch,matpair,global_cache);
    //   std::cout<<"unmatched task list "<<std::endl;
       curBatch.clear();
       for( std::vector<Task>::iterator iter = unmatched_task_list.begin(); iter != unmatched_task_list.end(); ++iter )
       {
           curBatch.push_back(*iter);
      //     std::cout<<(*iter).getTaskId()<<std::endl;
       }
  }
    else //No Aggregated matrices pair from CCU. Nodes_list,curBatch. Schedule in Baseline manner
  {
        int i =0;
        int NumberOfNodes = Nodes_list.size();
        if(NumberOfNodes < 1 ) return;
        for( std::vector<Task>::iterator iter = curBatch.begin(); iter != curBatch.end(); ++iter )
       {           
            Nodes_list[i%NumberOfNodes]->PJSNode.addTask(*iter);
            i++;
       }
        curBatch.clear();
  }
        
}

PJS::~PJS() {
    
}

void PJS::CheckForTasks()
{
    std::vector<Task> newTasks;
    while(!NodePJS_queue.empty()){
        Task t = NodePJS_queue.front();
        int i;
        for(i=0; i<job_list.size(); i++)
        {
            if(job_list[i].getJobId()==t.getJob_id()){
                std::vector<Task> retTasks = job_list[i].notifyFinishedTask(t.getTaskId());
                if(job_list[i].isFinished()){
                    stats.recordCompletedJob(job_list[i].getJobId(),job_list[i].getStartTime());
                }
                
                for(size_t i=0; i<retTasks.size(); i++){
                    
                    retTasks[i].setStartTime(stats.getClock());
                    
                    curBatch.push_back(retTasks[i]);
                }
                NodePJS_queue.pop();
                break;
            }
        }
    } 
}

void PJS::RecieveJobs(int num_jobs){
    std::vector<Job> newJobs = jobGen.GenerateJobs(num_jobs);
    for(size_t i=0; i<newJobs.size(); i++){
        Job job= newJobs[i];
        std::vector<Task> initialTasks = job.getFirstTasks();
        for(size_t j=0; j<initialTasks.size(); j++){
            
            initialTasks[j].setStartTime(stats.getClock());
            curBatch.push_back(initialTasks[j]);
        }
        job_list.push_back(job);
    }
    if(newJobs.size()==0){
        out_of_jobs=true;
    }
}
