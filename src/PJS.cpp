#include "PJS.h"
#include "Node.h"
#include "Task.h"

PJS::PJS() {
}

PJS::PJS(const PJS& orig) {
}


PJS::PJS(std::vector<Node *> Nodes_list) {
    
 PJS_thread_ptr = std::unique_ptr<std::thread>(new std::thread(&PJS::Start_PJS,this,Nodes_list));

}

void PJS::Start_PJS(std::vector<Node *> Nodes_list)
{
    //PJS constructocr
//creating dummy tasks
std::vector<Task> Task_list;
Task *t1 = new Task(1,30,1);
Task_list.push_back(*t1);
Task *t2 = new Task(2,10,6);
Task_list.push_back(*t2);
Task *t3 = new Task(3,20,4);
Task_list.push_back(*t3);
Task *t4 = new Task(4,80,7);
Task_list.push_back(*t4);
Task *t5 = new Task(5,90,2);
Task_list.push_back(*t5);
Task *t6 = new Task(6,70,5);
Task_list.push_back(*t6);
Task *t7 = new Task(7,60,6);
Task_list.push_back(*t7);
Task *t8 = new Task(8,50,3);
Task_list.push_back(*t8);
Task *t9 = new Task(9,40,5);
Task_list.push_back(*t9);
Task *t10 = new Task(10,320,5);
Task_list.push_back(*t10);
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


