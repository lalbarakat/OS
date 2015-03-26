#ifndef CCU_H
#define	CCU_H

#include <vector>
#include "Job.h"
#include "Task.h"
#include "Node.h"
#include "CCU_Node.h"
#include "CCU_PJS.h"

class CCU {
public:
    CCU(std::vector <Node*> _node_list);
    CCU(const CCU& orig);
    virtual ~CCU();
    int apply_matrix(Task t);
    void update_matrix();
    
private:
    void init_matrix();
    std::vector<std::vector<int>> wait_time_matrix;
    std::vector <Node*> node_list;
    

};

#endif	/* CCU_H */

