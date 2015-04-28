/* 
 * File:   Celda.cpp
 * Author: Alberto
 * 
 * Created on 1 de marzo de 2015, 20:08
 */

#include "../headers/Celda.h"
#include <iostream>
/**
 * CONSTRUCTORS
 */

Celda::Celda() {
}
Celda::Celda(const Celda& orig) {
}
Celda::~Celda() {
}

Celda::Celda(uint lx, uint ly, float x,float y,float w,float h,State s){
    lposition=sf::Vector2u(lx,ly);
    position=sf::Vector2f(x,y);
    size=sf::Vector2f(w,h);
    state=s;
    g=0;
    h=0;
    parent=NULL;
}

/**
 * GETTERS
 */
Celda* Celda::getParent(){
    return parent;
}
sf::Vector2u Celda::getLPos(){
    return lposition;
}
sf::Vector2f Celda::getPos(){
    return position;
}
sf::Vector2f Celda::getSize(){
    return size;
}
sf::Vector2f Celda::getCenter(){
    sf::Vector2f s(size.x/2,size.y/2);
    return position+s;
}
uint Celda::getG(){
    return g;
}
uint Celda::getH(){
    return h;
}
uint Celda::getF(){
    return g+h;
}

uint Celda::getValue(){
    return getF();
}
Celda::State Celda::getState(){
    return state;
}
/**
 * SETTERS
 */
void Celda::setParent(Celda* c){
    //if(c!=NULL)
        //std::cout<<"parent("<<lposition.x<<","<<lposition.y<<")->("<<c->getLPos().x<<","<<c->getLPos().y<<")"<<std::endl;
    parent=c;
}
void Celda::setCost(uint pg, uint ph){
    g=pg;
    h=ph;
}
void Celda::setState(State s){
    state=s;
}

/**
 * REST
 */

bool Celda::isPath(){
    return state==Celda::PATH || state==Celda::GROUND || state==Celda::SPAWN || state==Celda::NEXO;
}
void Celda::draw(sf::RenderWindow* w){
    //std::cout<<"Muestro celda: ("<<position.x<<","<<position.y<<"),("<<size.x<<","<<size.y<<")"<<std::endl;
    sf::RectangleShape r;
    r.setSize(size);
    r.setPosition(position);
    r.setOutlineColor(sf::Color::Black);
    r.setOutlineThickness(1);
    sf::Color c;
    switch(state){
        case Celda::GROUND:
            c=sf::Color::White;
            break;
        case Celda::OBSTACLE:
            c=sf::Color::Red;
            break;
        case Celda::TOWER:
            c=sf::Color::Cyan;
            break;
        case Celda::PATH:
            c=sf::Color::Green;
            break;
        case Celda::SPAWN:
        case Celda::NEXO:
            c=sf::Color::Yellow;
            break;
    }
    r.setFillColor(c);
    w->draw(r);
}