#include "PJS.h"
#include "Node.h"
#include "Task.h"
#include <set>

PJS::PJS() : jobGen("jobs.txt"){
}

PJS::PJS(const PJS& orig): jobGen("jobs.txt") {
}

PJS::PJS(std::vector<Node *> Nodes_list): jobGen("jobs.txt") {
    //Start_PJS(Nodes_list);
}

void PJS::Start_PJS(std::vector<Node *> Nodes_list)
{
    //PJS constructocr
    //Reading the aggregated wait time matrices from CCU_PJS
    if(!(PJS::CCUPJS.isEmpty())){
    CCUPJS.getMatrix();
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
}