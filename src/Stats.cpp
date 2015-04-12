/* 
 * File:   Stats.cpp
 * Author: Matthew
 * 
 * Created on April 12, 2015, 12:08 PM
 */

#include "Stats.h"
#include <fstream>
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

