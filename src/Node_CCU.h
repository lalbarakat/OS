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
#include <mutex>

class CCU;
class Node_CCU {
public:
    typedef std::vector <float> row_t;
    typedef std::vector <row_t> matrix_t;
    
    Node_CCU();
    Node_CCU(const Node_CCU& orig);
    virtual ~Node_CCU();
    std::pair<int, matrix_t> getWaitTimeMatrix();
    std::pair<int, matrix_t> peekWaitTimeMatrix();
    void addWaitTimeMatrix(int _id, matrix_t _mat);
    void addWaitTimeMatrix(std::pair<int, matrix_t> _pair);
    bool isEmpty();
    CCU* ccu=NULL;
private:
    std::queue <std::pair<int, matrix_t>> matrix_queue;
    std::mutex queue_mutex;
};

#endif	/* NODE_CCU_H */

