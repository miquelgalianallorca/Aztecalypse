/* 
 * File:   BinaryHeap.cpp
 * Author: Alberto
 * 
 * Created on 16 de marzo de 2015, 23:23
 */

#include "../headers/BinaryHeapCell.h"
#include <cmath>
#include <iostream>
#include <iterator>
#include <string.h>
#include <vector>

BinaryHeapCell::BinaryHeapCell() {
}

BinaryHeapCell::BinaryHeapCell(const BinaryHeapCell& orig) {
}

BinaryHeapCell::~BinaryHeapCell() {
}

std::vector<Celda*> BinaryHeapCell::getData(){
    return data;
}
uint BinaryHeapCell::size(){
    return data.size();
}
bool BinaryHeapCell::contains(Celda* c){
    return (std::find(data.begin(), data.end(), c) != data.end());
}
void BinaryHeapCell::swap(uint a, uint b){
    Celda* va=data[a];
    Celda* vb=data[b];
    std::vector<Celda*>::iterator bg=data.begin();
    
    data.erase(bg+a);
    data.insert(bg+a,vb);
    
    data.erase(bg+b);
    data.insert(bg+b,va);
}
void BinaryHeapCell::add(std::vector<Celda*> v){
    uint sz=v.size();
    for(uint i=0;i<sz;i++){
        add(v[i]);
    }
}
void BinaryHeapCell::add(Celda* v){
    //Obtengo el coste F de la celda
    uint value=v->getF();
    //indice que tendrá el elemento e índice de su padre
    uint rindex=data.size();
    //El índice se calcula así porque los elementos empiezan por 0
    uint rhalf=floor( (rindex+1)/2-1 );
    //Meto el elemento al final del vector
    data.push_back(v);
    //Mientras su padre sea mayor que el
    while(rindex!=0 && data[rhalf]->getF()>value){
        //display();
        //Lo cambio con su padre
        swap(rindex,rhalf);
        //std::cout<<"Cambio el elemento "<<rindex<<" por el "<<rhalf<<std::endl;
        //display();
        //Actualizo los índices
        rindex=rhalf;
        rhalf=floor( (rindex+1)/2-1 );
        //std::cout<<"Ahora comparo los elementos "<<rindex<<" y "<<rhalf<<std::endl;
    }
    //display();
}
Celda* BinaryHeapCell::getLowest(){
    std::vector<Celda*>::iterator bg=data.begin();
    uint sz,rindex,fchild,schild,v,vf,vs,lowest;
    v=0;vf=0;vs=0;
    //Obtengo el valor para devolver
    Celda* ret=data[0];
    sz=data.size();
    //Intercambio el último con el primero
    swap(0,sz-1);
    //y borro el que acabo de mover al último lugar
    data.pop_back();
    sz-=1;
    //indice que del primer elemento e índice de su primer hijo
    rindex=0;
    //El índice se calcula así porque los elementos empiezan por 0
    fchild=floor( (rindex+1)*2-1 );
    schild=fchild+1;
    
    v=(rindex<sz)?data[rindex]->getF():-1;
    vf=(fchild<sz)?data[fchild]->getF():-1;
    vs=(schild<sz)?data[schild]->getF():-1;
    
    //Mientras el padre sea mayor que sus dos hijos
    while(rindex<sz && (v>vf || v>vs)){
        lowest=(vf<vs)?fchild:schild;
        //Lo cambio con el menor de sus hijos
        swap(rindex,lowest);
        //display();
        //Actualizo los índices
        rindex=lowest;
        fchild=floor( (rindex+1)*2-1 );
        schild=fchild+1;
        //Actualizo los valores
        v=(rindex<sz)?data[rindex]->getF():-1;
        vf=(fchild<sz)?data[fchild]->getF():-1;
        vs=(schild<sz)?data[schild]->getF():-1;   
    }
    return ret;
}
void BinaryHeapCell::display(){
    uint sz=data.size();
    for(uint i=0;i<sz;i++)
        std::cout<<"["<<i<<"]->"<<data[i]->getF()<<" ";
    std::cout<<std::endl;
}