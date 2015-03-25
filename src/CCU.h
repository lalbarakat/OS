#ifndef CCU_H
#define	CCU_H
#include <vector>
#include "Job.h"
class CCU {
    using Matrix = std::vector<std::vector<int>>;
public:
    CCU();
    CCU(const CCU& orig);
    virtual ~CCU();
    int apply_matrix(Task t);
    void update_matrix();
    
    
private:
    Matrix mat;
    

};

#endif	/* CCU_H */

