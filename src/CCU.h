#ifndef CCU_H
#define	CCU_H

#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>

#include "Job.h"
#include "Task.h"
#include "Node.h"  //  
#include "CCU_Node.h"
#include "CCU_PJS.h"
#include "Globals.h"

class CCU {
public:
    CCU();
    CCU(std::vector <Node*> _node_list);
    CCU(const CCU& orig);
    virtual ~CCU();
    int apply_matrix(Task t);
    void update_matrix();
    void notify();
private:
    void init_matrix();
    std::vector<std::vector<int>> wait_time_matrix;
    std::vector <Node*> node_list;
    bool running;
    std::unique_ptr<std::thread> thread_ptr;
    std::condition_variable cv;
    std::mutex cv_mutex;
};

#endif	/* CCU_H */

