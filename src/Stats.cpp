/* 
 * File:   Stats.cpp
 * Author: Matthew
 * 
 * Created on April 12, 2015, 12:08 PM
 */

#include "Stats.h"
#include <fstream>
#include<ctime>
Stats::Stats():filename("output.txt"),filename_CPUUtil("output_cpuutil.csv"),filename_MemoryUtil("output_memoryutil.csv"),
        filename_NumberofTasks("output_numberoftasks.csv"),filename_JobCompletion("output_jobcompletion.txt"),jobCounter(0),taskCounter(0),clock(0) {
    std::ofstream out(filename, std::ofstream::trunc);
    //Need to do this to overwrite contents of previous run.
    out<<"Stats file"<<std::endl;
    out.close();
    
    out.open(filename_CPUUtil, std::ofstream::trunc);
    out<<""<<std::endl;
    out.close();
    
    out.open(filename_MemoryUtil, std::ofstream::trunc);
    out<<""<<std::endl;
    out.close();
    
    out.open(filename_NumberofTasks, std::ofstream::trunc);
    out<<""<<std::endl;
    out.close();
    
    out.open(filename_JobCompletion, std::ofstream::trunc);
    out<<""<<std::endl;
    out.close();
}

Stats::Stats(const Stats& orig) {
}

Stats::~Stats() {
}
void Stats::recordCompletedJob(int jobId){
    std::ofstream out(filename, std::ofstream::app);
    out<<"+Job(" << jobId << ") completed at" << clock << "." << std::endl;
    out.close();
    
    out.open(filename_JobCompletion, std::ofstream::app);
    //out.open(filename_JobCompletion);
    out<<clock<<" "<<jobId<<std::endl;
    out.close();
    
    jobCounter++;
}
void Stats::recordCompletedJob(int jobId, unsigned long long startTime){
    std::ofstream out(filename, std::ofstream::app);
    out<<"+Job(" << jobId << ") completed in" << (clock-startTime) << "." << std::endl;
    out.close();
    
    out.open(filename_JobCompletion, std::ofstream::app);
    //out.open(filename_JobCompletion);
    out<<clock-startTime<<" "<<jobId<<std::endl;
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
    
       float utilization = ((float)coresUsed) / totalCores;
       std::ofstream out(filename_CPUUtil, std::ofstream::app);
       out<<clock<<","<<utilization<<std::endl;
       out.close();
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
       float utilization = ((float)GBUsed) / totalGB;
       std::ofstream out(filename_MemoryUtil, std::ofstream::app);
       out<<clock<<","<<utilization<<std::endl;
       out.close();
    
    taskCounter++;
}
void Stats::recordNumTasksRead(int num_tasks){
    
    std::ofstream out(filename_NumberofTasks, std::ofstream::app);
    out<<clock<<","<<num_tasks<<std::endl;
    out.close();
}
void Stats::finalPrint(){
    std::ofstream out(filename, std::ofstream::app);
    out<<"Completed "<<jobCounter<<" jobs and "<<taskCounter<<" tasks in"
            <<clock<<" cycles."<<std::endl;
    out.close();
}
