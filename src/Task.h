#ifndef TASK_H
#define	TASK_H

class Task {
public:
    Task(int taskid, int cputime, int memoryrequired){
        task_id = taskid;
        CPU_time = cputime; 
        memory_required = memoryrequired;
    }
  
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

    int getTask_id() const {
        return task_id;
    }
    
private:
    // member variables
    int task_id; // task id unqiue for each task in a job.
    int CPU_time; // Amount of time CPU takes to execute the task.
    int memory_required; // Amount of Main Memory required to execute the task.

    
};

#endif	/* TASK_H */

