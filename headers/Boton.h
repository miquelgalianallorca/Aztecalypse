#ifndef BOTON_H
#define	BOTON_H
#include "GameState.h"
#include <SFML/Graphics.hpp>

class Boton {
public:
    Boton(GameState* gs, int tipo);
    Boton(const Boton& orig);
    virtual ~Boton();
    void update(sf::RenderWindow& window);
    sf::Sprite sp;
private:    
    float factor;
    int iniY;
    GameState* state;
};
#endif	/* BOTON_H */

