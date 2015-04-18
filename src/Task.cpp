#include "Task.h"
Task::Task() {
    job_id=-1;
    task_id=-1;
    CPU_time=0;
    no_op=true;
}

//Task::~Task() {
//}

Task::Task(int jobId, int taskid, int cputime, int memoryrequired,int coresrequired, bool isOppunrtinistic )
{
        job_id=jobId;
        task_id = taskid;
        CPU_time = cputime;
        memory_required = memoryrequired;
        cores_required = coresrequired;       
        isOppurtunistic = isOppunrtinistic;
        no_op=false;
}




