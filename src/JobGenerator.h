#ifndef JOBGENERATOR_H
#define	JOBGENERATOR_H

#include "JobGen_PJS.h"
#include "Job.h"
#include "Task.h"

#include<stdio.h>
#include<iostream>
#include<fstream>
#include<vector>
#include<list>
#include "Globals.h"

class JobGenerator {
public:
    JobGenerator(std::string filename);
   // JobGenerator(const JobGenerator& orig);
    virtual ~JobGenerator();
    std::vector<Job> GenerateJobs();
private:
     std::vector<Job> list_jobs;
     std::ifstream f_in;
};

#endif	/* JOBGENERATOR_H */

