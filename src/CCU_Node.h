#ifndef CCU_NODE_H
#define	CCU_NODE_H

#include <list>
#include <vector>
#include <queue>
#include "Block.h"

typedef std::vector<std::pair<Block,std::list<int>>> GlobalCache;

class CCU_Node {
public:
    CCU_Node();
    CCU_Node(const CCU_Node& orig);
    virtual ~CCU_Node();
    GlobalCache getGlobalCache();
    GlobalCache PeekGlobalCache();
    void addToGlobalCache(GlobalCache c);
    bool isCacheEmpty();
private:
    
    std::queue<GlobalCache> global_cache_queue;
};

#endif	/* CCU_NODE_H */

