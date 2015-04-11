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

bool CCU_PJS::isEmpty(){
    return AggregatedMatrices_queue.empty();
}

AggregatedMatPair CCU_PJS::PeekMatrix(){
    AggregatedMatPair m;
    if(!AggregatedMatrices_queue.empty()) {
        m= AggregatedMatrices_queue.front();
    }
    return m;
}