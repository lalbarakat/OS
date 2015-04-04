#include "Task.h"
//Task::Task() {
//}
//
//Task::~Task() {
//}

Task::Task(int taskid, int cputime, int memoryrequired, bool _no_op): 
        task_id(taskid),CPU_time(cputime), memory_required(memoryrequired),
        no_op(_no_op)
{
}
Task::Task(const Task& orig):task_id(orig.getTask_id()), 
        CPU_time(orig.getCPU_time()), memory_required(orig.getMemory_required())
{
}

