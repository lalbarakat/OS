#include "CCU.h"

void CCU::update_matrix(std::mutex* output_mutex){
    while(running){
        std::this_thread::yield();
    }
}

CCU::CCU(std::vector<Node*> _node_list, std::mutex* output_mutex) {
    node_list = _node_list;
    running = true;
    init_matrix();
    thread_ptr= std::unique_ptr<std::thread>(new std::thread(&CCU::update_matrix, this, output_mutex));
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


