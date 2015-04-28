
#include "../headers/Interpolacion.h"


Interpolacion::Interpolacion()
{
}

Interpolacion::Interpolacion(const Interpolacion& orig)
{
}

sf::Vector2f Interpolacion::interpolate(float f){
    sf::Vector2f pos;
    pos.x=f*posActual.x+(1-f)*posAnterior.x;
    pos.y=f*posActual.y+(1-f)*posAnterior.y;
    return pos;
}
void Interpolacion::update(sf::Vector2f u){
    posAnterior=posActual;
    posActual=sf::Vector2f(u);
}


Interpolacion::~Interpolacion()
{
}

