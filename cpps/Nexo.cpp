/* 
 * File:   Nexo.cpp
 * Author: Alberto
 * 
 * Created on 13 de abril de 2015, 13:25
 */

#include "../headers/Nexo.h"

Nexo::Nexo() {
}

Nexo::Nexo(const Nexo& orig) {
}

Nexo::Nexo(Celda* c, float vi){
    celda=c;
    vida_inicial=vi;
    vida=vida_inicial;
    
    sf::Texture *txt=new sf::Texture();
    if (!txt->loadFromFile("resources/nexo.png"))
    {
        std::cerr << "Error cargando la imagen orc.png";
        exit(0);
    }
    sf::Sprite sp(*txt);
    sp.scale(0.4,0.4);
    sp.setTextureRect(sf::IntRect(0,0,128,128));
    sp.setOrigin(64,64);
    setPosition(celda->getCenter());
    sprite=sp;;    
}

bool Nexo::isDead(){
    return vida<=0;
}

Celda* Nexo::getCelda(){
    return celda;
}
void Nexo::quitarVida(float d){
    vida-=d;
}

Nexo::~Nexo() {
}

