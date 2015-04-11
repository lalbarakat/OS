#include "CCU.h"
typedef std::pair<int,Node_CCU::matrix_t> nodeMatPair;
void CCU::update_matrix(){
    
    if(!Node::NodeCCU.isEmpty()){
        nodeMatPair p=Node::NodeCCU.getWaitTimeMatrix();
        std::cout<<"Got matrix from"<<p.first<<std::endl;
        //Aggregation goes here.
    }
}

void Aggregate_matrices()

CCU::CCU(std::vector<Node*> _node_list) {
    Node::NodeCCU.ccu=this;
    init_matrix();
}

CCU::CCU(){
}

CCU::CCU(const CCU& orig) {
}

CCU::~CCU() {
}

void CCU::init_matrix(){
    ;
}
int CCU::apply_matrix(Task t){
    ;
}
