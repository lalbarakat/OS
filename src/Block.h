/* 
 * File:   Block.h
 * Author: karthik
 *
 * Created on April 23, 2015, 10:50 PM
 */

#ifndef BLOCK_H
#define	BLOCK_H
#include <vector>
class Block {
public:
    Block();
    Block(int blockid, int fileid);
    Block(int blockid, int fileid,int size);    
    virtual ~Block();
    int get_block_id(){return block_id;}
    int get_file_id(){return file_id;}
    int get_size(){return size;}
private:
    int block_id;
    int file_id;
    int size = 0.10; //0.1 GB 
};

#endif	/* BLOCK_H */

