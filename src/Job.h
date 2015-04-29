#ifndef JOB_H
#define	JOB_H

#include "Task.h"
#include "Globals.h"

#include<stdio.h>
#include<iostream>
#include<list>
#include <vector>

class Job {
public:
    Job();
    Job(int jobid, int num_tasks, bool _isOppurtunistic=false);
    //Job(int jobid, std::vector <std::list<int> >& adlist, std::vector<Task> _tasks);
    //Job(const Job& orig);
    virtual ~Job();
    void addTask(Task t);
    int getJobId() const{
        return job_id;
    }
    //i should be dependent on j
    void addDependency(int i, int j);
    void printAdList();
    unsigned long long getStartTime() const {return start_time;}
    std::vector<Task> getFirstTasks();
    std::vector<Task> notifyFinishedTask(int task_id);
    bool isFinished();
private:
    int job_id;
    bool isOpportunistic;
    //Used to graph the graph
    std::vector <std::vector<int>> parent_list;
    std::vector <std::vector<int>> child_list;
    std::vector <Task> task_list;
    std::vector<bool> isComplete;
    void traverse(int i);
    bool arePredecessorsComplete(int task_id);
    unsigned long long start_time;
};

#endif	/* JOB_H */

