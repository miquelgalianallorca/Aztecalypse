/* 
 * File:   Camino.cpp
 * Author: Alberto
 * 
 * Created on 12 de abril de 2015, 13:59
 */

#include <vector>

#include "../headers/Camino.h"
using namespace std;

Camino::Camino() {
}

Camino::Camino(const Camino& orig) {
}

Camino::Camino(vector<Celda*> c) {
    camino=c;
}

Celda* Camino::getCell(int i){
    if(i<getSize())
        return camino[i];
    
    return NULL;
}
Celda* Camino::getStart(){
    return camino.front();
}
Celda* Camino::getEnd(){
    return camino.back();
}
int Camino::getSize(){
    return camino.size();
}

std::vector<Enemigo*> Camino::getUsuarios(){
    return usuarios;
}

Camino* Camino::getSubpath(Celda* s, Celda* e){
    std::vector<Celda*>::iterator start,end;
    bool founds=false,founde=false;
    
    if(camino.front()==s && camino.back()==e)
        return this;
    
    for(start=camino.begin();!founds && start!=camino.end();){
        if(*start==s)
            founds=true;
        else
            ++start;
    }
    
    for(end=camino.end();founds && !founde && end!=camino.begin();){
        if(*end==e){
            founde=true;
            ++end;
        }
        else
            --end;
    }
    
    if(founds && founde && start<end){
        
        return new Camino(vector<Celda*>(start,end));
    }else{
        return NULL;
    }
}

bool Camino::hasCell(Celda* c){
    return contains(camino,c);
}

void Camino::addUsuario(Enemigo* e){
    usuarios.push_back(e);
}

void Camino::removeUsuario(Enemigo* e){
    for(int a=0,size=usuarios.size();a<size;a++){
        if(usuarios[a]==e){
            usuarios.erase(usuarios.begin()+a);
            break;
        }
    }
}

void Camino::setStates(){
    for(int a=1,size=camino.size();a<size-1;a++){
        camino[a]->setState(Celda::PATH);
    }
}

void Camino::removeStates(){
    for(int a=1,size=camino.size();a<size-1;a++){
        if(camino[a]->getState()==Celda::PATH)
            camino[a]->setState(Celda::GROUND);
    }
}
Camino::~Camino() {
    camino.clear();
    usuarios.clear();
}

