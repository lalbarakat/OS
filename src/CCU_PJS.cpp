#include "CCU_PJS.h"

CCU_PJS::CCU_PJS() {
}

CCU_PJS::CCU_PJS(const CCU_PJS& orig) {
}

CCU_PJS::~CCU_PJS() {
}
void CCU_PJS::addMatrix(matrix_t m) {
    matrixqueue_mutex.lock();
    matrix_queue.push(m);
    matrixqueue_mutex.unlock();
}

matrix_t CCU_PJS::getMatrix() {
    matrix_t m;
    matrixqueue_mutex.lock();
    if(!matrix_queue.empty()) {
        m= matrix_queue.front();
        matrix_queue.pop();
    }
    matrixqueue_mutex.unlock();
    return m;
}

bool CCU_PJS::isEmpty(){
    std::lock_guard<std::mutex> lock(matrixqueue_mutex);
    return matrix_queue.empty();
}

matrix_t CCU_PJS::PeekMatrix(){
    matrix_t m;
     matrixqueue_mutex.lock();
    if(!matrix_queue.empty()) {
        m= matrix_queue.front();
    }
    matrixqueue_mutex.unlock();
    return m;
}
