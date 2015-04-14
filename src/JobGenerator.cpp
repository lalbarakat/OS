#include "JobGenerator.h"
#include <fstream>

JobGenerator::JobGenerator(std::string filename): f_in(filename){
    
}

//JobGenerator::JobGenerator(const JobGenerator& orig) {
//}

JobGenerator::~JobGenerator() {
    f_in.close();
}
Task getTask(std::ifstream& f_in){
   int task_id, cpu_time, memory, cores_used;
   f_in>>task_id;
   f_in>>cpu_time;
   f_in>>memory;
   f_in>>cores_used;
   Task t(task_id, cpu_time, memory, cores_used);
   return t;
}
std::vector<Job> JobGenerator::GenerateJobs() {
    int job_id, num_tasks;
    f_in>>job_id;
    f_in>>num_tasks;
    Job job(job_id, num_tasks);
    for(int i=0; i<num_tasks; i++){
        int num_dep;
        Task t=getTask(f_in);
        job.addTask(t);
        f_in>>num_dep;
        for(int j=0;j<num_dep;j++){
            int dep_id;
            f_in>>dep_id;
            job.addDependency(t.getTaskId(),dep_id);
        }
    }
}

/*
void JobGenerator::PrintJobs() {
    std::vector<Job>::iterator itr;
    for(itr=list_jobs.begin();itr!=list_jobs.end();itr++) {
        //Job *job = *itr;
        // cout<< "job id" << job->job_id;
        // cout<<"Graph";
    }
    

}
 */