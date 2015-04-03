#ifndef JOBGENERATOR_H
#define	JOBGENERATOR_H

#include "JobGen_PJS.h"
#include "Job.h"
#include "Task.h"

#include<stdio.h>
#include<iostream>
#include<vector>
#include<list>
#include "Globals.h"

class JobGenerator {
public:
    JobGenerator();
   // JobGenerator(const JobGenerator& orig);
    virtual ~JobGenerator();
    void GenereateJobs(std::vector <std::list<Task> > &Graph);
    void DFS(int el,std::vector <std::list<Task> > &adlist,int visited[]);
    void PrintJobs();
private:
     std::vector<Job> list_jobs;

};

#endif	/* JOBGENERATOR_H */

