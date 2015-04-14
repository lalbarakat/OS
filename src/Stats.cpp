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
}

Stats::Stats(const Stats& orig) {
}

Stats::~Stats() {
}

void Stats::recordCompletedJob(int jobId, unsigned long long startTime){
    std::ofstream out(filename);
    out<<"Job(" << jobId << ") completed in" << (clock-startTime) << "." << std::endl;
    out.close();
    jobCounter++;
}
void Stats::recordCompletedTask(int jobId,int taskId, unsigned long long startTime){
    std::ofstream out(filename);
    out<<"Task(" << taskId << ") of Job("<<
            jobId<<") completed in" << (clock-startTime) << "." << std::endl;
    out.close();
    taskCounter++;
}

void Stats::recordCpuUtilization()
{
    time_t now =time(0);
    std::ofstream out(filename);
    out<< "CPU Utilization :  cores used " << coresUsed <<" out of "<<totalCores<<" at " <<now<<std::endl;
    out.close();
    taskCounter++;
}

void Stats::recordMemoryUtilization()
{
    time_t now =time(0);
    std::ofstream out(filename);
    out<< "Memory Utilization :  Memory used " << GBUsed <<" out of "<<totalGB<<" at " <<now<< std::endl;
    out.close();
    taskCounter++;
}
void Stats::recordCompletedTask(int jobId, int taskId, time_t timeStamp)
{
    std::ofstream out(filename);
    out<<"Task(" << taskId << ") of Job("<<
            jobId<<") completed at" << timeStamp << "." << std::endl;
    out.close();
    taskCounter++;
    
}

void Stats::finalPrint(){
    std::ofstream out(filename);
    out<<"Completed "<<jobCounter<<" jobs and "<<taskCounter<<" tasks in"
            <<clock<<" cycles."<<std::endl;
    out.close();
}
