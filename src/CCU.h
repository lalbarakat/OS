#ifndef CCU_H
#define	CCU_H

#include <vector>
#include <thread>
#include <mutex>

#include "Job.h"
#include "Task.h"
#include "Node.h"  // By Laith we will use shared memory for communication 
#include "CCU_Node.h"
#include "CCU_PJS.h"

class CCU {
public:
    CCU(std::vector <Node*> _node_list, std::mutex& _output_mutex); // By Laith we will use shared memory for communication
    CCU(const CCU& orig);
    virtual ~CCU();
    int apply_matrix(Task t);
    void update_matrix();
    
private:
    void init_matrix();
    std::vector<std::vector<int>> wait_time_matrix;
    std::vector <Node*> node_list; // By Laith we will use shared memory for communication
    std::thread  update_thread;
    bool running;
    std::mutex output_mutex;
};

#endif	/* CCU_H */

