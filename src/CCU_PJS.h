#ifndef CCU_PJS_H
#define	CCU_PJS_H
#include "Globals.h"
#include <queue>

typedef std::pair<int, matrix_t> intMatPair;
typedef std::vector<intMatPair> AggregatedMatPair;
class CCU_PJS {
public:
    CCU_PJS();
    CCU_PJS(const CCU_PJS& orig);
    virtual ~CCU_PJS();
    void addMatrix(AggregatedMatPair m);
    AggregatedMatPair getMatrix();
    AggregatedMatPair PeekMatrix();
    bool isEmpty();
    
private:
    //std::queue<matrix_t> AggregatedMatrices_queue;
    std::queue<AggregatedMatPair> AggregatedMatrices_queue;
    

};

#endif	/* CCU_PJS_H */

