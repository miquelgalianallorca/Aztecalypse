#ifndef CELDA_H
#define	CELDA_H
#include <SFML/Graphics.hpp>
#include "BinaryHeap.h"
#include "Valuable.h"

class Celda : public Valuable<uint>, public sf::Drawable, public sf::Transformable{
public:
    enum State{TERRAIN,GROUND,TOWER,OBSTACLE,PATH,NEXO,SPAWN};
    /**
     * CONSTRUCTORS
     */
    
    Celda();    
    Celda(const Celda& orig);
    //lx ly x y width height
    Celda(uint,uint,float,float,float,float,State);
    //lpos pos size
    Celda(sf::Vector2u,sf::Vector2f,sf::Vector2f);
    
    virtual uint getValue();
    
    /**
     * GETTERS
     */
    
    uint getG();
    uint getH();
    uint getF();
    Celda* getParent();
    sf::Vector2u getLPos();
    sf::Vector2f getPos();
    sf::Vector2f getSize();
    sf::Vector2f getCenter();
    State getState();
    /**
     * SETTERS
     */
    
    void setState(State);
    void setParent(Celda*);
    void setCost(uint g, uint h);
    
    /**
     * REST
     */
    
    void draw(sf::RenderWindow*);
    bool isPath();
    virtual ~Celda();
private:
    State state;
    uint g;
    uint h;
    sf::Vector2f position;
    sf::Vector2u lposition;
    sf::Vector2f size;
    Celda* parent;
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform*=getTransform();
                
        sf::RectangleShape r;
        r.setSize(size);
        r.setPosition(position);
        r.setOutlineColor(sf::Color(0,0,0,80));
        r.setOutlineThickness(0.5);
        sf::Color c;
        switch(state){
            case Celda::GROUND:
                c=sf::Color::White;
                c=sf::Color::Transparent;
                break;
            case Celda::OBSTACLE:
                c=sf::Color::Red;
                c=sf::Color(255,0,0,150);
                break;
            case Celda::TOWER:
                c=sf::Color(255,128,0,200);
                break;
            case Celda::PATH:
                //c=sf::Color::Green;
                c=sf::Color(0,255,255,120);
                break;
            case Celda::SPAWN:
            case Celda::NEXO:
                c=sf::Color(255,255,0,150);
                break;
        }
        r.setFillColor(c);
        target.draw(r,states);
    }
};

#endif	/* CELDA_H */