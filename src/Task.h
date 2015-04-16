#ifndef TASK_H
#define	TASK_H
//#include "Globals.h"

class Task {
public:
   // Task();
    //virtual ~Task();
    Task(int jobId, int taskid, int cputime, int memoryrequired,int coresrequired,bool isOppurtunistic = false);
    
    
    
    void setCPU_time(int CPU_time) {
        this->CPU_time = CPU_time;
    }

    void setMemory_required(int memory_required) {
        this->memory_required = memory_required;
    }

    void setTask_id(int task_id) {
        this->task_id = task_id;
    }
    
    int getCPU_time() const {
        return CPU_time;
    }

    int getMemory_required() const {
        return memory_required;
    }

    int getTaskId() const {
        return task_id;
    }
    
    int getJob_id() const {
        return job_id;
    }
    void setNo_op(){
        no_op=true;
    }
    bool getNo_op() const{
        return no_op;
    }
    
    int getCores_required() const {
        return cores_required;
    }

    void setCores_required(int cores_required) {
        this->cores_required = cores_required;
    }

    
private:
    // member variables
    int job_id;// id of job of which task is a sub part.
    int task_id; // task id unqiue for each task in a job.
    int CPU_time; // Amount of time CPU takes to execute the task.
    int memory_required; // Amount of Main Memory required to execute the task.
    int cores_required;
    bool no_op;
    bool isOppurtunistic = false;
    
};

#endif	/* TASK_H */

