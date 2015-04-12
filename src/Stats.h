/* 
 * File:   Stats.h
 * Author: Matthew
 *
 * Created on April 12, 2015, 12:08 PM
 */

#ifndef STATS_H
#define	STATS_H
#include <string>

class Stats {
    
public:
    Stats();
    Stats(const Stats& orig);
    virtual ~Stats();
    //Print out some final statistics
    void finalPrint();
    //Print out a record of a completed task
    void recordCompletedTask(int jobId, int taskId, unsigned long long startTime);
    void recordCompletedTask(int jobId, int taskId, int startTime)=delete;
    void recordCompletedTask(int jobId, int taskId, unsigned int startTime)=delete;
    void recordCompletedTask(int jobId, int taskId, char startTime)=delete;
    //Print out a record of a completed job
    void recordCompletedJob(int jobId, unsigned long long startTime);
    void recordCompletedJob(int jobId, int startTime)=delete;
    void recordCompletedJob(int jobId, unsigned int startTime)=delete;
    void recordCompletedJob(int jobId, char startTime)=delete;
    //Print out a record of the CpuUtilization at one time stamp
    //Potentailly record CpuUtilization at various times.
    void recordCpuUtilization(int coresUsed, int totalCores);
    unsigned long long getClock(){return clock;};
    void incClock(){clock++;}
    
    
private:
    std::string filename;
    unsigned int jobCounter;
    unsigned int taskCounter;
    unsigned long long clock;
};

#endif	/* STATS_H */

