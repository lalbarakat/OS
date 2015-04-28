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

std::vector<Task> PJS::Greedy_matcher(std::vector<Node *> Nodes_list,std::vector<Task>Task_list,std::vector<intMatPair> matpair) //matpair is the list of aggregated wait time matrices.
{
    std::vector<int> matched_Nodes_list;
    std::vector<Task> unmatched_task_list(Task_list);
    
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
            matrix_t waittime_matrix = (*it).second;//matrix  
            int req = task.getCores_required();
            int mem = task.getMemory_required();
            if(waittime_matrix[req%2][mem%4] < min_time && waittime_matrix[req%2][mem%4]!=-1)
            {
                   min_time = waittime_matrix[task.getCores_required()%2][task.getMemory_required()%4];
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
    if(!(PJS::CCUPJS.isEmpty()) && curBatch.size()>0)
    {
        matpair =  CCUPJS.PeekMatrix();
       //Randomly allocate tasks oppurtunistically.
       for( std::vector<Task>::iterator iter = curBatch.begin(); iter != curBatch.end(); ++iter )
       {
             
             /*int r = rand()%100;
             if(r>80//2 in 10 are oppurtinsitic tasks. choosing them with 20% probability
               (*iter).SetTaskMode(1);//1 for oppurtunistic
             else*/
               (*iter).SetTaskMode(0);//0 for regular
       }
        
       std::vector<Task> unmatched_task_list = Greedy_matcher(Nodes_list,curBatch,matpair);
    //   std::cout<<"unmatched task list "<<std::endl;
       curBatch.clear();
       for( std::vector<Task>::iterator iter = unmatched_task_list.begin(); iter != unmatched_task_list.end(); ++iter )
       {
           curBatch.push_back(*iter);
      //     std::cout<<(*iter).getTaskId()<<std::endl;
       }
  }
    else //No Aggregated matrices pair from CCU. Nodes_list,curBatch. Schedule in Baseline manner.
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

void PJS::CheckForTasks(){
    std::vector<Task> newTasks;
    while(!NodePJS_queue.empty()){
        Task t = NodePJS_queue.front();
        int i;
        for(i=0; i<job_list.size(); i++){
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
