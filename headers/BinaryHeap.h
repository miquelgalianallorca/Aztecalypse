/* 
 * File:   BinaryHeap.h
 * Author: Alberto
 *
 * Created on 16 de marzo de 2015, 23:23
 */

#ifndef BINARYHEAP_H
#define	BINARYHEAP_H

#include "config.h"

class BinaryHeap {
public:
    BinaryHeap();
    BinaryHeap(const BinaryHeap& orig);
    virtual ~BinaryHeap();
    
    std::vector<uint> getData();
    
    void display();
    
    void swap(uint,uint);
    
    void add(uint);
    void add(std::vector<uint>);
    
    uint getLowest();
private:
    std::vector<uint> data;
};

#endif	/* BINARYHEAP_H */

