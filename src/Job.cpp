#include "Job.h"
#include <deque>
Job::Job() {
}
Job::Job(int id, int num_tasks):job_id(id)
{
    parent_list.resize(num_tasks);
    child_list.resize(num_tasks);
}
/*
Job::Job(int jobid, std::vector<std::list<Task> >& graph, std::vector<Task> _tasks): 
job_id(jobid), task_list(_tasks), adjacency_list(graph){
    for(int i=0; i<_tasks.size();i++){
        isComplete.push_back(false);
    }
}
*/
//Job::Job(const Job& orig) {
//}

Job::~Job() {
}

void Job::addTask(Task t){
    isComplete.push_back(false);
    task_list.push_back(t);
}
void Job::addDependency(int i, int j){
    parent_list[i].push_back(j);
    child_list[j].push_back(i);
}
bool Job::isFinished(){
    for(int i=0; i<isComplete.size(); i++){
        if(!isComplete[i]){
            return false;
        }
    }
    return true;
}
bool Job::arePredecessorsComplete(int task_id){
    for(int dep_id : parent_list[task_id]){
        if(!isComplete[dep_id]){
            return false;
        }
    }
    return true;
}
std::vector<Task> Job::getNextTasks(){
    std::vector<Task> ret_vec;
    for(size_t i=0; i<task_list.size(); i++){
        if(arePredecessorsComplete(i)){
            ret_vec.push_back(task_list[i]);
        }
    }
    return ret_vec;
}

void Job::notifyFinishedTask(int task_id){
    isComplete[task_id]=true;
}