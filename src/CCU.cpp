#include "CCU.h"

void CCU::update_matrix(){
    while(running){
        std::unique_lock<std::mutex> lk(cv_mutex);
        cv.wait(lk,[]{return !Node::NodeCCU.isEmpty();});
        
    }
}

CCU::CCU(std::vector<Node*> _node_list) {
    node_list = _node_list;
    running = true;
    init_matrix();
    thread_ptr= std::unique_ptr<std::thread>(new std::thread(&CCU::update_matrix, this));
}

CCU::CCU(const CCU& orig) {
}

CCU::~CCU() {
    if(running){
        running = false;
        thread_ptr->join();
    }
}

void CCU::init_matrix(){
    ;
}
int CCU::apply_matrix(Task t){
    ;
}

void CCU::notify(){
    cv.notify_one();
}
