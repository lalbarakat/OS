#include "CCU.h"

void CCU::update_matrix(){
    while(running){
        std::unique_lock<std::mutex> lk(cv_mutex);
        cv.wait(lk,[this]{return !Node::NodeCCU.isEmpty()||!running;});
        
        if(!running)
            break;
        
        
    }
}

CCU::CCU(std::vector<Node*> _node_list) {
    Node::NodeCCU.ccu=this;
    running = true;
    init_matrix();
    thread_ptr= std::unique_ptr<std::thread>(new std::thread(&CCU::update_matrix, this));
}

CCU::CCU(const CCU& orig) {
}

CCU::~CCU() {
    if(running){
        running = false;
        cv.notify_one();
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
