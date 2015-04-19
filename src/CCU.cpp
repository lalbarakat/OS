#include "CCU.h"
#include "PJS.h"

typedef std::pair<int,matrix_t> nodeMatPair;
void CCU::update_matrix(){
    
    while(!Node::NodeCCU.isEmpty()){
        nodeMatPair p=Node::NodeCCU.getWaitTimeMatrix();
       // std::cout<<"Got matrix from"<<p.first<<std::endl;
        //Aggregating by adding the pair(Node  and it's wait time matrix) to the list.
        VectorofMatrices.push_back(p);
        //Aggregation goes here.
    }
     if(!(PJS_ptr->CCUPJS.isEmpty()))
     {
         PJS_ptr->CCUPJS.getMatrix();
     }
   PJS_ptr->CCUPJS.addMatrix(VectorofMatrices);
}



CCU::CCU(std::vector<Node*> node_list,PJS *PJS_obj) {
    Node::NodeCCU.ccu=this;
    init_matrix();
    PJS_ptr = PJS_obj;
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
