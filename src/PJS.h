#ifndef PJS_H
#define	PJS_H
#include <vector>
#include "PJS_Node.h"
#include "Node.h"
#include "JobGenerator.h"
#include "CCU_PJS.h"
#include "JobGen_PJS.h"
#include "Globals.h"

class PJS {
public:
    CCU_PJS CCUPJS;
    PJS();
    PJS(std::vector<Node *> Nodes_list);
    PJS(const PJS& orig);
    virtual ~PJS();  
    void resize( matrix_t& m, unsigned rows, unsigned cols, float value = 0.0 )
    {
        // first, resize all the available columns
        unsigned min = (m.size() < rows) ? m.size() : rows;
        for (unsigned row = 0; row < min; row++)
          {
          m[ row ].resize( cols, value );
          }
        // next, resize the rows -- adding complete new columns if necessary
        m.resize( rows, row_t( cols, value ) );
    }
    void Start_PJS(std::vector<Node *> Nodes_list);
    void RecieveJobs();
    void CheckForTasks();
private:
    matrix_t wait_time_matrix;    
    std::vector <int> list_of_nodes;
    std::vector <Job> job_list;
    std::vector <Task> curBatch;
    JobGenerator jobGen;
    };

#endif	/* PJS_H */

