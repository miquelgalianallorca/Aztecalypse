/* 
 * File:   BinaryHeapCell.h
 * Author: Alberto
 *
 * Created on 19 de marzo de 2015, 17:49
 */

#ifndef BINARYHEAPCELL_H
#define	BINARYHEAPCELL_H

#include "config.h"
#include "Celda.h"

class BinaryHeapCell {
public:
    BinaryHeapCell();
    BinaryHeapCell(const BinaryHeapCell& orig);
    virtual ~BinaryHeapCell();
    
    std::vector<Celda*> getData();
    
    void display();
    
    void swap(uint,uint);
    
    void add(Celda*);
    void add(std::vector<Celda*>);
    
    uint size();
    bool contains(Celda*);
    Celda* getLowest();
private:
    std::vector<Celda*> data;
};

#endif	/* BINARYHEAPCELL_H */

