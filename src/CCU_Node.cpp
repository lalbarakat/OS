#include "CCU_Node.h"

CCU_Node::CCU_Node() {
}

CCU_Node::CCU_Node(const CCU_Node& orig) {
}

CCU_Node::~CCU_Node() {
}

GlobalCache CCU_Node::getGlobalCache()
{
    GlobalCache c;
    if(!global_cache_queue.empty())
    {
        c = global_cache_queue.front();
        global_cache_queue.pop();
    }
    return c; 
}


GlobalCache CCU_Node::PeekGlobalCache()
{
    GlobalCache c;
    if(!global_cache_queue.empty())
    {
        c = global_cache_queue.front();        
    }
    return c;
 }
void CCU_Node::addToGlobalCache(GlobalCache c)
{
    global_cache_queue.push(c);
}

bool CCU_Node::isCacheEmpty(){
    return global_cache_queue.empty();
}


