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
    unsigned long long getClock(){return clock;}
    void incClock(){clock++;}
    void incCoresUSed(){coresUsed++;}
    void inctotalCores(){totalCores++;}
    void incGBUSed(){GBUsed++;}
    void inctotalGB(){totalGB++;}
    
    unsigned long getCoresUSed(){return coresUsed;}
    void setCoresUSed(int coresused){coresUsed =coresused;}
    void settotalCores(int totalcores){totalCores = totalcores;}
    void setGBUSed(int gbused ){GBUsed = gbused;}
    void settotalGB(int totalgb){totalGB = totalgb;}
        
    
private:
    std::string filename;
    unsigned int jobCounter;
    unsigned int taskCounter;
    unsigned long long clock;
    unsigned long coresUsed;
    unsigned long totalCores;
    unsigned long GBUsed;
    unsigned long totalGB;
};

#endif	/* STATS_H */

