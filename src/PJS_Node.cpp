#include "PJS_Node.h"
#include "Task.h"

PJS_Node::PJS_Node() {
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
    Task t(0,0,0);
    t.setNo_op();
    queue_mutex.lock();
    if(!task_queue.empty()){
        Task t= task_queue.front();
        task_queue.pop();
    }
    queue_mutex.unlock();
    return t;
}
