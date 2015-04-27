/* 
 * File:   File.h
 * Author: karthik
 *
 * Created on April 23, 2015, 10:52 PM
 */

#ifndef FILE_H
#define	FILE_H
#include"Block.h"

class File {
public:
    File();
    File(const File& orig);
    int get_file_id(){return file_id;}
    virtual ~File();
private:
    int file_id;
    std::vector<Block> Blocks_list;
};

#endif	/* FILE_H */

