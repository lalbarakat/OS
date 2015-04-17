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
//            matched_node->PJSNode.addTask(task);
            cout<<" node matched "<<matched_node->getId()<<" with task "<<task.getTaskId()<<endl;
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
    if(!(PJS::CCUPJS.isEmpty())){
     matpair =  CCUPJS.getMatrix();
    }
      
    std::vector<Task> Task_list;
    Task t1(0,1,30,1,2);
    Task_list.push_back(t1);
    Task t2(0,2,10,6,4);
    Task_list.push_back(t2);
    Task t3(0,3,20,4,2);
    Task_list.push_back(t3);
    Task t4(0,4,80,7,2);
    Task_list.push_back(t4);
    Task t5(0,5,90,2,4);
    Task_list.push_back(t5);
    Task t6(0,6,70,5,2);
    Task_list.push_back(t6);
    Task t7(0,7,60,6,4);
    Task_list.push_back(t7);
    Task t8(0,8,50,3,2);
    Task_list.push_back(t8);
    Task t9(0,9,40,5,1);
    Task_list.push_back(t9);
    Task t10(0,10,320,5,3);
    Task_list.push_back(t10);
    //send 10 tasks to 5 nodes.
    std::vector<Task> unmatched_task_list = Greedy_matcher(Nodes_list,curBatch,matpair);
    curBatch.clear();
    std::cout<<"unmatched task list "<<std::endl;
    for( std::vector<Task>::iterator iter = unmatched_task_list.begin(); iter != unmatched_task_list.end(); ++iter )
    {
        curBatch.push_back(*iter);
        std::cout<<(*iter).getTaskId()<<std::endl;
    }
    

int i=0;
for (std::vector<Node *>::iterator it = Nodes_list.begin() ; it != Nodes_list.end(); ++it)
{
    (*it)->PJSNode.addTask(Task_list[i]);
    i++;
    (*it)->PJSNode.addTask(Task_list[i]);
    i++;
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
                for(size_t i=0; i<retTasks.size(); i++){
                    curBatch.push_back(retTasks[i]);
                }
                NodePJS_queue.pop();
                break;
            }
        }
    } 
}

void PJS::RecieveJobs(){
    std::vector<Job> newJobs = jobGen.GenerateJobs();
    for(size_t i=0; i<newJobs.size(); i++){
        Job j= newJobs[i];
        std::vector<Task> initialTasks= j.getFirstTasks();
        for(size_t j=0; j<initialTasks.size(); j++){
            curBatch.push_back(initialTasks[j]);
        }
        job_list.push_back(j);
    }
    if(newJobs.size()==0){
        out_of_jobs=true;
    }
}