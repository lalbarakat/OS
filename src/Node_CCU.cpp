/* 
 * File:   Node_CCU.cpp
 * Author: saasbook
 * 
 * Created on April 1, 2015, 8:52 PM
 */

#include "Node_CCU.h"
#include "CCU.h"

Node_CCU::Node_CCU():ccu(NULL) {
}

Node_CCU::Node_CCU(const Node_CCU& orig) {
}

Node_CCU::~Node_CCU() {
}

void Node_CCU::addWaitTimeMatrix(intMatPair _pair){
    matrix_queue.push(_pair);
}
void Node_CCU::addWaitTimeMatrix(int _id, matrix_t _mat){
    intMatPair p(_id, _mat);
    this->addWaitTimeMatrix(p);
}

bool Node_CCU::isEmpty(){
    return matrix_queue.empty();
}

intMatPair Node_CCU::getWaitTimeMatrix(){
    matrix_t empty;
    std::pair<int, matrix_t> a(-1, empty);
    if(!matrix_queue.empty()){
        a.first=matrix_queue.front().first;
        a.second=matrix_queue.front().second;
        matrix_queue.pop();
    }
    return a;
}

intMatPair Node_CCU::peekWaitTimeMatrix(){
    matrix_t empty;
    intMatPair a(-1, empty);
    if(!matrix_queue.empty()){
        a.first=matrix_queue.front().first;
        a.second=matrix_queue.front().second;
    }
    return a;
}