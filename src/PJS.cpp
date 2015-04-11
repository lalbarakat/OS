#include "PJS.h"
#include "Node.h"
#include "Task.h"

PJS::PJS() {
}

PJS::PJS(const PJS& orig) {
}


PJS::PJS(std::vector<Node *> Nodes_list) {
    Start_PJS(Nodes_list);
}

void PJS::Start_PJS(std::vector<Node *> Nodes_list)
{
    //PJS constructocr
    //Reading the aggregated wait time matrices from CCU_PJS
    if(!(PJS::CCUPJS.isEmpty())){
    CCUPJS.getMatrix();
    }
std::vector<Task> Task_list;
Task t1(1,30,1,2);
Task_list.push_back(t1);
Task t2(2,10,6,4);
Task_list.push_back(t2);
Task t3(3,20,4,2);
Task_list.push_back(t3);
Task t4(4,80,7,2);
Task_list.push_back(t4);
Task t5(5,90,2,4);
Task_list.push_back(t5);
Task t6(6,70,5,2);
Task_list.push_back(t6);
Task t7(7,60,6,4);
Task_list.push_back(t7);
Task t8(8,50,3,2);
Task_list.push_back(t8);
Task t9(9,40,5,1);
Task_list.push_back(t9);
Task t10(10,320,5,3);
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

