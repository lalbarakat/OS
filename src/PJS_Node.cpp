#include "PJS_Node.h"
#include "Task.h"

PJS_Node::PJS_Node(std::condition_variable* _cv, std::mutex* _condition_mutex): 
        cv(_cv), condition_mutex(_condition_mutex)
{
}

PJS_Node::PJS_Node(const PJS_Node& orig) {
}

PJS_Node::~PJS_Node() {
}

void PJS_Node::addTask(Task t){
    queue_mutex.lock();
    task_queue.push(t);
    queue_mutex.unlock();
}

Task PJS_Node::getTask(){
    Task t(0,0,0, true);
    queue_mutex.lock();
    if(!task_queue.empty()){
        t= task_queue.front();
        task_queue.pop();
    }
    queue_mutex.unlock();
    return t;
}
