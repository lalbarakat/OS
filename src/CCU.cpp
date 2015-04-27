#include "CCU.h"
#include "PJS.h"


void CCU::update_matrix(){
    
    VectorofMatrices.clear();
    while(!Node::NodeCCU.isMatrixEmpty()){
        nodeMatPair p=Node::NodeCCU.getWaitTimeMatrix();
       // std::cout<<"Got matrix from"<<p.first<<std::endl;
        //Aggregating by adding the pair(Node  and it's wait time matrix) to the list.
        VectorofMatrices.push_back(p);
        //Aggregation goes here.
    }
     if(!(PJS_ptr->CCUPJS.isMatrixEmpty()))
     {
         PJS_ptr->CCUPJS.getMatrix();
     }
   PJS_ptr->CCUPJS.addMatrix(VectorofMatrices);
}

void CCU::update_Global_cache()
{
    global_cache.clear();
    while(!Node::NodeCCU.isCacheEmpty())
    {
        localCache empty;
        localCachePair p(-1,empty);
        p = Node::NodeCCU.getCache();
       // PACMan Co-ordinator Aggregate the caches from all the nodes.
        Aggregate_cache(p.first,p.second);
    }
    
     while(!(PJS_ptr->CCUPJS.isCacheEmpty()))
     {
         PJS_ptr->CCUPJS.getGlobalCache();
     }
   PJS_ptr->CCUPJS.addToGlobalCache(global_cache);
   //Also send the global cache to individual nodes, so that they use it for LIFE and LFU_F implementation
   for(int i =0;i<node_list.size() ; i++)
   {
       //Clear all the existing cache in the queue.
       while(!node_list[i]->CCUNode.isCacheEmpty())
       {
           node_list[i]->CCUNode.getGlobalCache();
       }
       //Add to the queue.
       node_list[i]->CCUNode.addToGlobalCache(global_cache);
   }
    
}

int CCU::IsPresentInCache(Block b)
{
 for(int i =0;i < global_cache.size();i++)   
 {
     if(global_cache[i].first.get_block_id() == b.get_block_id() && global_cache[i].first.get_file_id() == b.get_file_id())
     {
         return i;
     }         
 }
 return -1;
}

void CCU::Aggregate_cache(int node_id,localCache lcache )
{
    
    for(int i =0;i<lcache.size();i++)
    {
        Block b = lcache[i].first;
        //check if Block B is present in Global Cache.
        int index =0;
        if((index = IsPresentInCache(b))!= -1)
        {
            global_cache[index].second.push_back(node_id);
            //If Block is already present in Global Cache. Find the pair and append to pair.second
            
        }
        else
        {  
            std::list<int> dummy;
            dummy.push_back(node_id);
            global_cache.push_back(std::make_pair(b,dummy));//If not create a new pair
        }        
               
    }
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
