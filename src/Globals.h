/* 
 * File:   Globals.h
 * Author: Matthew
 *
 * Created on April 3, 2015, 12:19 PM
 */

#ifndef GLOBALS_H
#define	GLOBALS_H
#include "Stats.h"
#include <vector>
#include<queue>
#include"Task.h"

typedef std::vector <float> row_t;
typedef std::vector <row_t> matrix_t;
extern Stats stats;

//#ifndef NodePJS_QUEUE
//#define	NodePJS_QUEUE
extern std::queue<Task> NodePJS_queue;
//#endif

#endif	/* GLOBALS_H */

