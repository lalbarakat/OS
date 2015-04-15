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
std::vector<Task> Job::getFirstTasks(){
    std::vector<Task> ret_vec;
    for(size_t i=0; i<task_list.size(); i++){
        if(arePredecessorsComplete(i)){
            ret_vec.push_back(task_list[i]);
        }
    }
    return ret_vec;
}

std::vector<Task> Job::notifyFinishedTask(int task_id){
    std::vector<Task> ret;
    //The task was resent just return an empty vector
    if(isComplete[task_id]){
        return ret;
    }
    isComplete[task_id]=true;
    for(int i=0; i<child_list[task_id].size();i++){
        int id=child_list[task_id][i];
        if(arePredecessorsComplete(id)){
            ret.push_back(task_list[id]);
        }
    }
    return ret;
}