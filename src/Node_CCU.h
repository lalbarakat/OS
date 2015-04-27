/* 
 * File:   Node_CCU.h
 * Author: saasbook
 *
 * Created on April 1, 2015, 8:52 PM
 */

#ifndef NODE_CCU_H
#define	NODE_CCU_H
#include "Globals.h"
#include <utility>
#include <vector>
#include <queue>

typedef std::pair<int, matrix_t> intMatPair;
typedef std::vector<std::pair<Block,int>> localCache;
typedef std::pair<int,localCache> localCachePair;

class CCU;
class Node_CCU {
public:
    
    Node_CCU();
    Node_CCU(const Node_CCU& orig);
    virtual ~Node_CCU();
    intMatPair getWaitTimeMatrix();
    intMatPair peekWaitTimeMatrix();
    void addWaitTimeMatrix(int _id, matrix_t _mat);
    void addWaitTimeMatrix(intMatPair _pair);
    bool isMatrixEmpty();
    bool isCacheEmpty();
    localCachePair getCache();
    localCachePair PeekCache();
    void addToCache(localCachePair c);
    CCU* ccu;
private:
    std::queue <intMatPair> matrix_queue;
    std::queue<localCachePair> global_cache_queue;
};

#endif	/* NODE_CCU_H */

