#ifndef PJS_NODE_H
#define	PJS_NODE_H
#include <queue>
#include <mutex>
#include "Task.h"
#include "Globals.h"
class PJS_Node {
public:
    PJS_Node();
    PJS_Node(const PJS_Node& orig);
    virtual ~PJS_Node();
    void addTask(Task t);
    Task getTask();
private:
    std::queue<Task> task_queue;
    std::mutex queue_mutex;
};

#endif	/* PJS_NODE_H */

