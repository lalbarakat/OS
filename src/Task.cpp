#include "Task.h"
//Task::Task() {
//}
//
//Task::~Task() {
//}

Task::Task(int taskid, int cputime, int memoryrequired,int coresrequired)
{
        task_id = taskid;
        CPU_time = cputime;
        memory_required = memoryrequired;
        cores_required = coresrequired;       
}


