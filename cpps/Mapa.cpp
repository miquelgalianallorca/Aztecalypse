/* 
 * File:   Mapa.cpp
 * Author: Alberto
 * 
 * Created on 1 de marzo de 2015, 20:05
 */

#include "../headers/Mapa.h"
#include <iostream>
/**
 * CONSTRUCTORS
 */

Mapa::Mapa() {
}
Mapa::Mapa(const Mapa& orig) {
}

Mapa::Mapa(float csz,sf::Vector2f tam,sf::Vector2f p){
    uint filas, columnas;
    
    filas=(unsigned int)tam.x/csz;
    columnas=(unsigned int)tam.y/csz;
    csize=sf::Vector2u(filas, columnas);
    setPosition(p);
    size=tam;
    
    celdas=new Celda*[filas];
    for (uint i=0; i < filas; i++)
        celdas[i]=new Celda[columnas];
    
    for(uint i=0;i<filas;i++)
        for(uint j=0;j<columnas;j++)
            celdas[i][j]=Celda(i,j,csz*i,csz*j,csz,csz,Celda::GROUND);
    
    sf::Texture *orc=new sf::Texture();
    if (!orc->loadFromFile("resources/background.png"))
    {
        std::cerr << "Error cargando la imagen player.png";
        exit(0);
    }
    sf::Sprite enemy(*orc);
    enemy.setTextureRect(sf::IntRect(0,0,1280,600));
    background=enemy;
}

/**
 * GETTERS
 */

Celda* Mapa::getCell(uint x, uint y){
    if(x>=0 && x<csize.x && y>=0 && y<=csize.y)
        return &celdas[x][y];
    return NULL;
}
Celda** Mapa::getMap(){return celdas;}
sf::Vector2f Mapa::getSize(){return size;}
sf::Vector2u Mapa::getCSize(){return csize;}

std::vector<Nexo*> Mapa::getNexos(){
    return nexos;
}


/**
 * SETTERS
 */

void Mapa::addNexo(Celda* c,float v){
    nexos.push_back(new Nexo(c,v));
    c->setState(Celda::NEXO);
}

Nexo* Mapa::getNexo(Celda* c){
    Nexo* n=NULL;
    for(int a=0,size=nexos.size();n==NULL && a<size;a++){
        if(nexos[a]->getCelda()==c)
            n=nexos[a];
    }
    return n;
}

/**
 * COSAS DE PATHFINDING
 */

uint Mapa::distance(Celda* ci,Celda* cf){
    sf::Vector2u i=ci->getLPos();
    sf::Vector2u f=cf->getLPos();
    return (abs(f.x-i.x)+abs(f.y-i.y));
}
Celda* Mapa::switchLowestF(std::vector<Celda*>* open,std::vector<Celda*>* closed){
    int index=-1;
    Celda* switched=NULL;
    uint size=open->size();
    uint lowest,aux;
    for(uint i=0;i<size;i++){
        aux=open->at(i)->getF();
        if(i==0 || aux<=lowest){
            lowest=aux;
            index=i;
        }
    }
    if(index!=-1){
        switched=open->at(index);
        open->erase(open->begin()+index);
        closed->push_back(switched);
        return switched;
    }
    return NULL;
}
Celda* Mapa::switchLowestF2(BinaryHeapCell* open,std::vector<Celda*>* closed){
    Celda* switched=open->getLowest();
    closed->push_back(switched);
    return switched;
}
std::vector<Celda*> Mapa::findPath2(Celda* start, Celda* end){
    sf::Clock c;
    //Inicializo la lista abierta, la cerrada y la que contendrá los vecinos
    BinaryHeapCell open_list;
    std::vector<Celda*> closed_list, neigh;
    Celda* current;
    Celda* aux;
    //Tamano del vector de vecinos
    uint szn;
    
    //Meto en la lista el nodo inicial y calculo sus costes
    start->setParent(NULL);
    calculateCost(start,end);
    open_list.add(start);
    
    while( !(open_list.size()==0 || contains(closed_list, end)) ){
        //Muevo la celda con menor coste F a la lista cerrada
        current=switchLowestF2(&open_list,&closed_list);
        //std::cout<<"closed.add["<<current->getLPos().x<<","<<current->getLPos().y<<"]"<<std::endl;
        //Obtengo los vecinos de esa celda
        neigh=getNeighbours(current);
        szn=neigh.size();
        //Los recorro
        for(uint i=0;i<szn;i++){
            aux=neigh[i];
            //Si esta en la lista abierta
            if(open_list.contains(aux)){
                //Si el camino al vecino es mas corto desde el nodo actual que
                //el que tenia anteriormente
                if(aux->getG() > current->getG()+distance(current,aux)){
                    aux->setParent(current);
                    calculateCost(aux,end);
                }
            //Si no lo esta
            }else if(!contains(closed_list,aux)){
                aux->setParent(current);
                calculateCost(aux,end);
                open_list.add(aux);
            }
        }
        //system("pause>nul");
    }
    std::vector<Celda*> path;
    if(contains(closed_list,end)){
        aux=closed_list[closed_list.size()-1];
        while(!contains(path,start)){
            //std::cout<<"path.add["<<aux->getLPos().x<<","<<aux->getLPos().y<<"]"<<std::endl;
            //system("pause>nul");
            path.push_back(aux);
            aux=aux->getParent();
        }
    }
    
    std::cout<<"Con monticulo:"<<c.getElapsedTime().asMicroseconds()<<" mcs."<<std::endl;
    return path;
}
std::vector<Celda*> Mapa::findPath(Celda* start, Celda* end){
    sf::Clock c;
    //Inicializo la lista abierta, la cerrada y la que contendrá los vecinos
    std::vector<Celda*> open_list, closed_list, neigh;
    Celda* current;
    Celda* aux;
    //Tamano del vector de vecinos
    uint szn;
    
    open_list.clear();
    closed_list.clear();
    //Meto en la lista el nodo inicial y calculo sus costes
    start->setParent(NULL);
    calculateCost(start,end);
    open_list.push_back(start);
    
    while( !(open_list.size()==0 || contains(closed_list, end)) ){
        //Muevo la celda con menor coste F a la lista cerrada
        current=switchLowestF(&open_list,&closed_list);
        //std::cout<<"closed.add["<<current->getLPos().x<<","<<current->getLPos().y<<"]"<<std::endl;
        //Obtengo los vecinos de esa celda
        neigh=getNeighbours(current);
        szn=neigh.size();
        //Los recorro
        for(uint i=0;i<szn;i++){
            aux=neigh[i];
            //Si esta en la lista abierta
            if(contains(open_list,aux)){
                //Si el camino al vecino es mas corto desde el nodo actual que
                //el que tenia anteriormente
                if(aux->getG() > current->getG()+distance(current,aux)){
                    aux->setParent(current);
                    calculateCost(aux,end);
                }
            //Si no lo esta
            }else if(!contains(closed_list,aux)){
                aux->setParent(current);
                calculateCost(aux,end);
                open_list.push_back(aux);
            }
        }
        //system("pause>nul");
    }
    std::vector<Celda*> path;
    
    if(contains(closed_list,end)){
        aux=closed_list[closed_list.size()-1];
        while(!contains(path,start)){
            //std::cout<<"path.add["<<aux->getLPos().x<<","<<aux->getLPos().y<<"]"<<std::endl;
            //system("pause>nul");
            //path.push_back(aux);
            path.insert(path.begin(),aux);
            aux=aux->getParent();
        }
    }
    //std::cout<<"Sin monticulo:"<<c.getElapsedTime().asMicroseconds()<<" mcs."<<std::endl;
    return path;
}
void Mapa::calculateCost(Celda* current, Celda* end){
    Celda* parent=current->getParent();
    uint g,h;
    g=0;
    if(parent!=NULL){
        g=parent->getG()+distance(parent,current);
    }
    h=distance(current,end);
    current->setCost(g,h);
}
std::vector<Celda*> Mapa::getNeighbours(Celda* c){
    uint x,y;
    sf::Vector2u pos=c->getLPos();
    x=pos.x;
    y=pos.y;
    std::vector<Celda*> n;
    int nx, ny;
    for(int i=-1;i<2;i++){
        for(int j=-1;j<2;j++){
            nx=x-i;
            ny=y-j;
            //No diagonal, no el mismo, traspasable
            if((x==nx || y==ny) && !(x==nx && y==ny) && isPath(nx,ny))
                n.push_back(&celdas[nx][ny]);
        }
    }
    return n;
}
bool Mapa::isPath(int x, int y){
    if(x>=0 && x<csize.x && y>=0 && y<csize.y)
        return celdas[x][y].isPath();
    return false;
}

/**
 * REST
 */

Mapa::~Mapa() {
}

