/* 
 * File:   Stats.cpp
 * Author: Matthew
 * 
 * Created on April 12, 2015, 12:08 PM
 */

#include "Stats.h"
#include <fstream>
#include<ctime>
Stats::Stats():filename("output.txt"),jobCounter(0),taskCounter(0),clock(0) {
    std::ofstream out(filename, std::ofstream::trunc);
    //Need to do this to overwrite contents of previous run.
    out<<"Stats file"<<std::endl;
    out.close();
}

Stats::Stats(const Stats& orig) {
}

Stats::~Stats() {
}
void Stats::recordCompletedJob(int jobId){
    std::ofstream out(filename, std::ofstream::app);
    out<<"Job(" << jobId << ") completed at" << clock << "." << std::endl;
    out.close();
    jobCounter++;
}
void Stats::recordCompletedJob(int jobId, unsigned long long startTime){
    std::ofstream out(filename, std::ofstream::app);
    out<<"Job(" << jobId << ") completed in" << (clock-startTime) << "." << std::endl;
    out.close();
    jobCounter++;
}

void Stats::recordCompletedTask(int jobId,int taskId){
    std::ofstream out(filename, std::ofstream::app);
    out<<"Task(" << taskId << ") of Job("<<
            jobId<<") completed at" << clock<< "." << std::endl;
    out.close();
    taskCounter++;
}

void Stats::recordCompletedTask(int jobId,int taskId, unsigned long long startTime){
    std::ofstream out(filename, std::ofstream::app);
    out<<"Task(" << taskId << ") of Job("<<
            jobId<<") completed in" << (clock-startTime) << "." << std::endl;
    out.close();
    taskCounter++;
}

void Stats::recordCpuUtilization()
{
    if(coresUsed!=prevCores){
        std::ofstream out(filename, std::ofstream::app);
        out<< "CPU Utilization :  cores used " << coresUsed <<" out of "<<totalCores<<" at " <<clock<<std::endl<<std::endl;
        out.close();
        prevCores=coresUsed;
    }
    taskCounter++;
}

void Stats::recordMemoryUtilization()
{
    if(GBUsed!=prevGB){
        std::ofstream out(filename, std::ofstream::app);
        out<< "Memory Utilization :  Memory used " << GBUsed <<" out of "<<totalGB<<" at " <<clock<< std::endl;
        out.close();
        prevGB=GBUsed;
    }
    taskCounter++;
}

void Stats::finalPrint(){
    std::ofstream out(filename, std::ofstream::app);
    out<<"Completed "<<jobCounter<<" jobs and "<<taskCounter<<" tasks in"
            <<clock<<" cycles."<<std::endl;
    out.close();
}
