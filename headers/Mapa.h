#ifndef MAPA_H
#define	MAPA_H

#include "Celda.h"
#include "BinaryHeapCell.h"
#include "config.h"
#include "Nexo.h"

class Mapa : public sf::Drawable, public sf::Transformable{
public:
    /**
     * CONSTRUCTORES
     */
    
    Mapa();
    Mapa(const Mapa& orig);
    Mapa(sf::Vector2u,sf::Vector2f,sf::Vector2f);
    Mapa(float,sf::Vector2f,sf::Vector2f);
    
    /**
     * GETTERS
     */
    
    Celda* getCell(uint, uint);
    Celda** getMap();
    sf::Vector2f getSize();
    sf::Vector2u getCSize();
    
    Nexo* getNexo(Celda*);
    std::vector<Nexo*> getNexos();
    
    /**
     * SETTERS
     */
    
    void setNexo(Celda*);
    void addNexo(Celda*,float);
    
    /**
     * PATHFINDING
     */
    
    std::vector<Celda*> findPath(Celda*, Celda*);
    std::vector<Celda*> findPath2(Celda*, Celda*);
    bool isPath(int, int);
    virtual ~Mapa();
    
private:
    Celda** celdas;
    sf::Vector2f position;
    sf::Vector2f size;
    sf::Vector2u csize;
    
    sf::Sprite background;
    
    std::vector<Nexo*> nexos;
    
    //Devuelve la distancia de manhattan entre dos celdas
    uint distance(Celda*, Celda*);
    //Calcula los costed g y h para una celda dada la celda final
    void calculateCost(Celda*, Celda*);
    //Devuelve los vecinos de una celda
    std::vector<Celda*> getNeighbours(Celda*);
    //Cambia elemento con conste F más bajo de un vector a otro
    Celda* switchLowestF(std::vector<Celda*>*,std::vector<Celda*>*); 
    Celda* switchLowestF2(BinaryHeapCell*,std::vector<Celda*>*); 
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform*=getTransform();
        
        target.draw(background);
        for(int i=0;i<csize.x;i++){
            for(int j=0;j<csize.y;j++){
                target.draw(celdas[i][j],states);
            }
        }
        for(int i=0;i<nexos.size();i++){
            target.draw(*nexos[i],states);
        }
    }
};
#endif	/* MAPA_H */