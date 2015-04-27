/* 
 * File:   Block.cpp
 * Author: karthik
 * 
 * Created on April 23, 2015, 10:50 PM
 */

#include "Block.h"

Block::Block(){
;
}

Block::Block(int blockid,int fileid) {
   block_id = blockid;
   file_id = fileid;
}

Block::Block(int blockid, int fileid,int s)
{
   block_id = blockid;
   file_id = fileid;
   size = s;
}


Block::~Block() {
}

