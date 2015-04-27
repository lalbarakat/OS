#include "CCU_PJS.h"

CCU_PJS::CCU_PJS() {
}

CCU_PJS::CCU_PJS(const CCU_PJS& orig) {
}

CCU_PJS::~CCU_PJS() {
}
void CCU_PJS::addMatrix(AggregatedMatPair m) {
    AggregatedMatrices_queue.push(m);
}

AggregatedMatPair CCU_PJS::getMatrix() {
    AggregatedMatPair m;
    if(!AggregatedMatrices_queue.empty()) {
        m= AggregatedMatrices_queue.front();
        AggregatedMatrices_queue.pop();
    }
    return m;
}

GlobalCache CCU_PJS::getGlobalCache()
{
    GlobalCache c;
    if(!global_cache_queue.empty())
    {
        c = global_cache_queue.front();
        global_cache_queue.pop();
    }
    return c; 
}


GlobalCache CCU_PJS::PeekGlobalCache()
{
    GlobalCache c;
    if(!global_cache_queue.empty())
    {
        c = global_cache_queue.front();        
    }
    return c;
 }
void CCU_PJS::addToGlobalCache(GlobalCache c)
{
    global_cache_queue.push(c);
}

bool CCU_PJS::isCacheEmpty(){
    return global_cache_queue.empty();
}

bool CCU_PJS::isMatrixEmpty(){
    return AggregatedMatrices_queue.empty();
}

AggregatedMatPair CCU_PJS::PeekMatrix(){
    AggregatedMatPair m;
    if(!AggregatedMatrices_queue.empty()) {
        m= AggregatedMatrices_queue.front();
    }
    return m;
}