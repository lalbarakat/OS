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
#include "Block.h"

typedef std::pair<int,matrix_t> nodeMatPair;
typedef std::vector<std::pair<Block,int>> localCache;
typedef std::pair<int,localCache> localCachePair;

typedef std::pair<int, matrix_t> intMatPair;
typedef std::vector<intMatPair> AggregatedMatPair;
typedef std::vector<std::pair<Block,std::list<int>>> Global_Cache;//Vector of "block and list of node id"

class CCU {
public:
    CCU();
    CCU(std::vector <Node*> _node_list,PJS *obj);
    CCU(const CCU& orig);
    virtual ~CCU();
    int apply_matrix(Task t);
    void update_matrix();
    AggregatedMatPair getVectorofMatrices();
    void update_Global_cache();
    void Aggregate_cache(int node_id,localCache lcache );
    int IsPresentInCache(Block b);
private:
    void init_matrix();
    std::vector<std::vector<int>> wait_time_matrix;
    std::vector <Node*> node_list;
    PJS *PJS_ptr;    
    AggregatedMatPair VectorofMatrices;
    //PACMan implementation
    Global_Cache global_cache;
};

#endif	/* CCU_H */

