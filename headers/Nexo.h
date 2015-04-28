#ifndef NEXO_H
#define	NEXO_H

#include "Celda.h"
#include <iostream>
#include <SFML/Graphics.hpp>

class Nexo : public sf::Drawable, public sf::Transformable{
public:
    Nexo();
    Nexo(const Nexo& orig);
    Nexo(Celda*, float);
    
    void quitarVida(float d);
    bool isDead();
    Celda* getCelda();
    virtual ~Nexo();
private:
    Celda* celda;
    float vida_inicial,vida;
    sf::Sprite sprite;
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform*=getTransform();
        
        sf::Vector2f size(80,15);
        
        sf::RectangleShape vidar(size);
        vidar.setFillColor(sf::Color(100,0,0));
        vidar.setOutlineColor(sf::Color::Black);
        vidar.setOutlineThickness(1);
        vidar.move(-size.x/2,-sprite.getTextureRect().height/2-15);
        
        
        float length=size.x*vida/vida_inicial;
        length=(length<0)?0:length;
        sf::RectangleShape vidav(sf::Vector2f(length,size.y));
        vidav.setFillColor(sf::Color(0,100,0));
        vidav.setOutlineColor(sf::Color::Black);
        vidav.setOutlineThickness(1);
        vidav.move(-size.x/2,-sprite.getTextureRect().height/2-15);
        
        sf::Font font;
        if (!font.loadFromFile("resources/opensansbold.ttf"))
        {
            std::cout<<"Fuenteeeeeeeeeeeee"<<std::endl;
        }
        sf::Text text;
        text.setFont(font);
        text.setString(convertInt(vida).append(" / ").append(convertInt(vida_inicial)));
        text.setCharacterSize(15);
        text.move(-30,-sprite.getTextureRect().height/2-17);
        text.setColor(sf::Color::White);
        
        target.draw(vidar,states);
        target.draw(vidav,states);
        
        target.draw(text,states);
        
        target.draw(sprite,states);
    }
};
#endif	/* NEXO_H */