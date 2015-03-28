#include "CCU.h"

CCU::CCU(std::vector<Node*> _node_list, std::mutex& _output_mutex) {
    node_list = _node_list;
    output_mutex = _output_mutex;
    running = true;
    init_matrix();
    update_thread(this->update_matrix);
}

CCU::CCU(const CCU& orig) {
}

CCU::~CCU() {
    if(running){
        running = false;
        update_thread.join();
    }
}

void CCU::init_matrix(){
    ;
}
int CCU::apply_matrix(Task t){
    ;
}

void CCU::update_matrix(){
    while(running){
        std::this_thread::yield();
    }
}
