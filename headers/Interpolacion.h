#ifndef INTERPOLACION_H
#define	INTERPOLACION_H
#include "SFML.h"
#include <vector>

class Interpolacion {
public:
    Interpolacion();
    Interpolacion(const Interpolacion& orig);
    void update(sf::Vector2f);
    sf::Vector2f interpolate(float);
    
    
    virtual ~Interpolacion();
    sf::Vector2f posActual;
    sf::Vector2f posAnterior;
};

#endif	/* INTERPOLACION_H */

