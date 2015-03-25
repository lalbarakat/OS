#ifndef JOB_H
#define	JOB_H

#include "Task.h"

#include<stdio.h>
#include<iostream>
#include<list>
#include <vector>

class Job {
public:
    Job();
    Job(int jobid, std::vector <std::list<Task> > &graph);
    //Job(const Job& orig);
    virtual ~Job();
private:
    int job_id;
    std::vector <std::list<Task> > adlist;

};

#endif	/* JOB_H */

