#include "Job.h"

Job::Job() {
}

Job::Job(int jobid, std::vector<std::list<Task> >& graph) {
    job_id = jobid;
    adlist = graph;
}
//Job::Job(const Job& orig) {
//}

Job::~Job() {
}

