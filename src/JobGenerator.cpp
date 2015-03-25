#include "JobGenerator.h"

JobGenerator::JobGenerator() {
}

//JobGenerator::JobGenerator(const JobGenerator& orig) {
//}

JobGenerator::~JobGenerator() {
}

void JobGenerator::GenereateJobs(std::vector <std::list<Task> > &Graph) {
    Job *job_obj = new Job(1,Graph);
    list_jobs.push_back(*job_obj);
}

void JobGenerator::DFS(int el, std::vector<std::list<Task> >& adlist, int visited[]) {
    // cout<<" element is "<<el;
    /*std::list<task> listt = adlist[el];
    for(std::list<task>::iterator k = listt.begin();k!=listt.end();k++) {
        if(visited[*k]==0) {
            visited[*k] = 1;
            DFS(*k,adlist,visited);
        }
    }
    */

}

void JobGenerator::PrintJobs() {
    std::vector<Job>::iterator itr;
    for(itr=list_jobs.begin();itr!=list_jobs.end();itr++) {
        //Job *job = *itr;
        // cout<< "job id" << job->job_id;
        // cout<<"Graph";
    }
    

}