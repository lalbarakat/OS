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
    task_queue.push(t);
}
bool PJS_Node::isEmpty(){
    return task_queue.empty();
}
Task PJS_Node::getTask(){
    Task t(0,0,0,0, true);
    if(!task_queue.empty()){
        t= task_queue.front();
        task_queue.pop();
    }
    
    return t;
}

Task PJS_Node::PeekTask(){
    Task t(0,0,0,0, true);
    if(!task_queue.empty()){
        t= task_queue.front();
    }
    return t;
}
