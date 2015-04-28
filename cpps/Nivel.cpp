/* 
 * File:   Nivel.cpp
 * Author: Alberto
 * 
 * Created on 22 de abril de 2015, 11:40
 */

#include <iostream>
#include <string.h>
#include <SFML/Graphics.hpp>
#include "../headers/FactoriaEnemigo.h"
#include "../headers/Nivel.h"
#include "../headers/Boton.h"
#include "../headers/Torreta.h"
#include "../headers/rapidxml.hpp"
#include "../headers/rapidxml_utils.hpp"
#include "../headers/Mapa.h"
using namespace std;
using namespace rapidxml;

Nivel::Nivel(char* file, GameState* gs) {
    
    
    sf::Texture *txt=new sf::Texture();
    if (!txt->loadFromFile("resources/hud.png"))
    {
        std::cerr << "Error cargando la imagen hud.png";
        exit(0);
    }
    sf::Sprite sp(*txt);
    sp.setTextureRect(sf::IntRect(0,0,1280,120));
    sp.setPosition(0,600);
    bg=sp;
    
    gold=0;
    score=0;
    archivo = file;
    int nexoX,nexoY,factX,factY = 0;
    FactoriaEnemigo* f;
    
    m = new Mapa(60.f,sf::Vector2f(1280,600),sf::Vector2f(0,0));
    
    rapidxml::file<> xmlFile(archivo); // Default template is char
    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlFile.data());
    xml_node<> *node = doc.first_node();
    xml_attribute<> *attr = node->first_attribute();
    
    nexoX = atoi(attr->value());
    nexoY = atoi(attr->next_attribute()->value());
    
    node = node->first_node();
    
    while(node && strcmp(node->name(),"factoria")==0){
        attr = node->first_attribute();
        factX = atoi(attr->value());
        factY = atoi(attr->next_attribute()->value());
        f = new FactoriaEnemigo(m->getCell(factX,factY),m->getCell(nexoX,nexoY),m , gs);
        factorias.push_back(f);
        node = node->next_sibling();
    }
    
}

Nivel::Nivel(const Nivel& orig) {
}

Nivel::~Nivel() {
}

Nivel::Nivel(int id){
    
}

//El numero de ronda debe ser el mismo de la ronda que toca(Ej.: Ronda 3 -> num=3)
//Dificultad -> dif=0: facil; dif=1: normal; dif=2: dificil;
void Nivel::cargaRonda(int num, int dif){
    int i=0;
    rapidxml::file<> xmlFile(archivo); // Default template is char
    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlFile.data());
    xml_node<> *node = doc.first_node();
    xml_attribute<> *attr = node->first_attribute();
    
    node = node->first_node();
    while(node && strcmp(node->name(),"dificultad")!=0){
        node = node->next_sibling();
    }
    
    if(node){
        for(i=0; node && i<dif; i++)
            node = node->next_sibling();
        
        if(node)
        node=node->first_node();
        for(i=1; node && i<num; i++)
            node = node->next_sibling();
        
        if(node)
            node=node->first_node();
        
        while(node){
            attr = node->first_attribute();
            if(strcmp(attr->value(),"normal")==0)
                factorias[atoi(attr->next_attribute()->value())]->createEnemyEspera(Enemigo::NORMAL);
            else
                if(strcmp(attr->value(),"rapido")==0)
                    factorias[atoi(attr->next_attribute()->value())]->createEnemyEspera(Enemigo::RAPIDO);
                else
                    if(strcmp(attr->value(),"tanque")==0)
                        factorias[atoi(attr->next_attribute()->value())]->createEnemyEspera(Enemigo::TANQUE); 
            node = node->next_sibling();
        }
    }else{
        cout<<"FIN DEL NIVEL"<<endl;
    }
}

void Nivel::update(){
    for(int a=0,size=factorias.size();a<size;a++){
        factorias[a]->update();
        gold+=factorias[a]->getGold();
        score+=factorias[a]->getScore();
    }
    for(int a=0,size=torretas.size();a<size;a++){
        for(int b=0,sizeB=factorias.size();b<sizeB;b++){
            torretas[a]->update(factorias[b]->getEnemigos());
        }
    }
}

Mapa* Nivel::getMapa(){
    return m;
}

std::vector<FactoriaEnemigo*> Nivel::getFactorias(){
    return factorias;
}

bool Nivel::creaTorreta(int x, int y, uint ti){
    Celda* cell = m->getCell(x,y);
    if(cell!=NULL){
        for(int i=0; i<factorias.size();i++)
            if(!factorias[i]->checkPaths(cell,Celda::TOWER))
                return false;
        for (vector<Torreta*>::iterator it = torretas.begin(); it != torretas.end(); ){
            if( cell == (*it)->getCelda() ){
                delete * it;  
                it = torretas.erase(it);
            }else{
                ++it;
            }
        }
        
        Torreta* t;
        switch(ti){
        case 0:
            t = new TorretaBase(&game_state);
            break;
        case 1:
             t = new Torreta1(&game_state);
            break;
        case 2:
             t = new Torreta2(&game_state);
            break;
        case 3:
             t = new Torreta3(&game_state);
            break;
        case 4:
             t = new Torreta11(&game_state);
            break;
        case 5:
             t = new Torreta12(&game_state);
            break;
        case 6:
             t = new Torreta21(&game_state);
            break;
        case 7:
             t = new Torreta22(&game_state);
            break;
        case 8:
             t = new Torreta31(&game_state);
            break;
        case 9:
             t = new Torreta31(&game_state);
            break;
        }
        t->setCelda(cell);
        torretas.push_back(t);
    }
    return false;
}