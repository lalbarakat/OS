#include "PJS_Node.h"
#include "Task.h"

PJS_Node::PJS_Node()
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
bool PJS_Node::isEmpty(){
    std::lock_guard<std::mutex> lock(queue_mutex);
    return task_queue.empty();
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

Task PJS_Node::PeekTask(){
    Task t(0,0,0, true);
    queue_mutex.lock();
    if(!task_queue.empty()){
        t= task_queue.front();
    }
    queue_mutex.unlock();
    return t;
}
