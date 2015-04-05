#ifndef CCU_PJS_H
#define	CCU_PJS_H
#include "Globals.h"
#include <queue>
#include <mutex>
#include <condition_variable>


typedef std::vector <float> row_t;
typedef std::vector <row_t> matrix_t;

class CCU_PJS {
public:
    CCU_PJS();
    CCU_PJS(const CCU_PJS& orig);
    virtual ~CCU_PJS();
    void addMatrix(matrix_t m);
    matrix_t getMatrix();
    matrix_t PeekMatrix();
    bool isEmpty();
private:
    std::queue<matrix_t> matrix_queue;
    std::mutex matrixqueue_mutex;

};

#endif	/* CCU_PJS_H */

