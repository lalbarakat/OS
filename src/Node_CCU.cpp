/* 
 * File:   Node_CCU.cpp
 * Author: saasbook
 * 
 * Created on April 1, 2015, 8:52 PM
 */

#include "Node_CCU.h"
#include "CCU.h"

Node_CCU::Node_CCU() {
}

Node_CCU::Node_CCU(const Node_CCU& orig) {
}

Node_CCU::~Node_CCU() {
}

void Node_CCU::addWaitTimeMatrix(std::pair<int,matrix_t> _pair){
    queue_mutex.lock();
    matrix_queue.push(_pair);
    queue_mutex.unlock();
    ccu->notify();
}
void Node_CCU::addWaitTimeMatrix(int _id, matrix_t _mat){
    std::pair<int,matrix_t> p(_id, _mat);
    this->addWaitTimeMatrix(p);
}

bool Node_CCU::isEmpty(){
    std::lock_guard<std::mutex> lk(queue_mutex);
    return matrix_queue.empty();
}

std::pair<int, Node_CCU::matrix_t> Node_CCU::getWaitTimeMatrix(){
    matrix_t empty;
    std::pair<int, matrix_t> a(-1, empty);
    queue_mutex.lock();
    if(!matrix_queue.empty()){
        a.first=matrix_queue.front().first;
        a.second=matrix_queue.front().second;
        matrix_queue.pop();
    }
    queue_mutex.unlock();
    return a;
}

std::pair<int, Node_CCU::matrix_t> Node_CCU::peekWaitTimeMatrix(){
    matrix_t empty;
    std::pair<int, matrix_t> a(-1, empty);
    queue_mutex.lock();
    if(!matrix_queue.empty()){
        a.first=matrix_queue.front().first;
        a.second=matrix_queue.front().second;
    }
    queue_mutex.unlock();
    return a;
}