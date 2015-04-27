#ifndef CCU_PJS_H
#define	CCU_PJS_H
#include "Globals.h"
#include <queue>
#include <list>
#include <vector>
#include <algorithm>
#include "Node.h"

typedef std::pair<int, matrix_t> intMatPair;
typedef std::vector<intMatPair> AggregatedMatPair;
typedef std::vector<std::pair<Block,std::list<int>>> GlobalCache;

class CCU_PJS {
public:
    CCU_PJS();
    CCU_PJS(const CCU_PJS& orig);
    virtual ~CCU_PJS();
    GlobalCache getGlobalCache();
    GlobalCache PeekGlobalCache();
    void addToGlobalCache(GlobalCache c);
    void addMatrix(AggregatedMatPair m);
    AggregatedMatPair getMatrix();
    AggregatedMatPair PeekMatrix();
    bool isMatrixEmpty();
    bool isCacheEmpty();
    
private:
    std::queue<GlobalCache> global_cache_queue;
    //std::queue<matrix_t> AggregatedMatrices_queue;
    std::queue<AggregatedMatPair> AggregatedMatrices_queue;
    //Global cache
    
    

};

#endif	/* CCU_PJS_H */

