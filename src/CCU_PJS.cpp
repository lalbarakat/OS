#include "CCU_PJS.h"

CCU_PJS::CCU_PJS() {
}

CCU_PJS::CCU_PJS(const CCU_PJS& orig) {
}

CCU_PJS::~CCU_PJS() {
}
void CCU_PJS::addMatrix(matrix_t m) {
    matrix_queue.push(m);
}

matrix_t CCU_PJS::getMatrix() {
    matrix_t m;
    if(!matrix_queue.empty()) {
        m= matrix_queue.front();
        matrix_queue.pop();
    }
    return m;
}

bool CCU_PJS::isEmpty(){
    return matrix_queue.empty();
}

matrix_t CCU_PJS::PeekMatrix(){
    matrix_t m;
    if(!matrix_queue.empty()) {
        m= matrix_queue.front();
    }
    return m;
}