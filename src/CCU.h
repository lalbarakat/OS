#ifndef CCU_H
#define	CCU_H

#include <vector>

#include "Job.h"
#include "Task.h"
#include "Node.h"  //  
#include "CCU_Node.h"
#include "CCU_PJS.h"
#include "Globals.h"
#include "PJS.h"

typedef std::pair<int, matrix_t> intMatPair;
typedef std::vector<intMatPair> AggregatedMatPair;

class CCU {
public:
    CCU();
    CCU(std::vector <Node*> _node_list,PJS *obj);
    CCU(const CCU& orig);
    virtual ~CCU();
    int apply_matrix(Task t);
    void update_matrix();
    AggregatedMatPair getVectorofMatrices();
private:
    void init_matrix();
    std::vector<std::vector<int>> wait_time_matrix;
    std::vector <Node*> node_list;
    PJS *PJS_ptr;
    AggregatedMatPair VectorofMatrices;
};

#endif	/* CCU_H */

