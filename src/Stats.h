/* 
 * File:   Stats.h
 * Author: Matthew
 *
 * Created on April 12, 2015, 12:08 PM
 */

#ifndef STATS_H
#define	STATS_H
#include <string>
#include <ctime>

class Stats {
    
public:
    Stats();
    Stats(const Stats& orig);
    virtual ~Stats();
    //Print out some final statistics
    void finalPrint();
    //Print out a record of a completed task
    void recordCompletedTask(int jobId, int taskId);
    void recordCompletedTask(int jobId, int taskId, unsigned long long startTime);
    void recordCompletedTask(int jobId, int taskId, int startTime)=delete;
    void recordCompletedTask(int jobId, int taskId, unsigned int startTime)=delete;
    void recordCompletedTask(int jobId, int taskId, char startTime)=delete;
    //Print out a record of a completed job
    void recordCompletedJob(int jobId);
    void recordCompletedJob(int jobId, unsigned long long startTime);
    void recordCompletedJob(int jobId, int startTime)=delete;
    void recordCompletedJob(int jobId, unsigned int startTime)=delete;
    void recordCompletedJob(int jobId, char startTime)=delete;
    //Print out a record of the CpuUtilization at one time stamp
    //Potentailly record CpuUtilization at various times.
    void recordCpuUtilization();
    void recordCpuUtilization(int coresUsed, int totalCores);
    //Potentailly record Memory Utilization at various times.
    void recordMemoryUtilization();
    void recordMemoryUtilization(int GBUsed, int totalGB);
    
    void recordNumTasksRead(int num_tasks);
    unsigned long long getClock(){return clock;}
    void incClock(){clock++;}
    void incCoresUSed(){coresUsed++;}
    void inctotalCores(int cores){totalCores+=cores;}
    void incGBUSed(){GBUsed++;}
    void incGBUSed(int gbused){GBUsed+= gbused; }
    void inctotalGB(int GB){totalGB+=GB;}
    
    void incQueueSize(int size){queueSize += size;}
    
    unsigned long getCoresUSed(){return coresUsed;}
    void setCoresUSed(int coresused){coresUsed =coresused;}
    void settotalCores(int totalcores){totalCores = totalcores;}
    void setGBUSed(int gbused ){GBUsed = gbused;}
    void settotalGB(int totalgb){totalGB = totalgb;}
    void setQueueSize(int size){queueSize = size;}
    int getQueueSize(){ return queueSize;}    
    
private:
    std::string filename;
    std::string filename_CPUUtil;
    std::string filename_MemoryUtil;
    std::string filename_NumberofTasks;
    std::string filename_JobCompletion;
    unsigned int jobCounter;
    unsigned int taskCounter;
    unsigned long long clock;
    
    unsigned long prevCores=1;
    unsigned long coresUsed;
    unsigned long totalCores;
    
    unsigned long queueSize;
    
    unsigned long prevGB=1;
    unsigned long GBUsed;
    unsigned long totalGB;
};

#endif	/* STATS_H */

