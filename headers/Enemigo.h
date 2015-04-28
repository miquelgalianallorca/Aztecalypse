#ifndef ENEMIGO_H
#define	ENEMIGO_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "config.h"
#include "Celda.h"
#include "Camino.h"
#include "GameState.h"
#include "Efecto.h"
#include "Interpolacion.h"

using namespace std;
class Enemigo : public sf::Drawable, public sf::Transformable, public Interpolacion{
public:
    enum TiposEnemigo{NORMAL, TANQUE, RAPIDO};
    /**
     * CONSTRUCTORES
     */
    Enemigo();
    Enemigo(const Enemigo& orig);
    Enemigo(float, float, uint, uint, uint, GameState*, sf::Texture* t);
    //Destructor
    ~Enemigo();
    /**
     * GETTERS
     */
    Camino* getPath();
    float getLife();
    float getSpeed();
    Celda* getCelda();
    float getDamage();
    float getCasillasRestantes();
    int getTeleport();
    float getGold(){return gold;}
    float getScore(){return score;}
    /**
     * SETTERS
     */
    
    void teleportToPath(Camino*);
    void setPath(Camino*);
    void setCelda(Celda*);
    void setPositionAtCell(Celda*);
    
    /**
     * SEGUIMIENTO DEL CAMINO
     */
    
    /**
     * Cambia la direccion en la que el enemigo se mueve cuando llega al centro 
     * de su proxima celda
     */
    void cambiarDireccion();
    
    /**
     * Cambia la celda del camino en la que se encuentra el enemigo 
     * cuando entra en la siguente
     */
    void cambiarCelda();
    
    /**
     * Actualiza la celda, la direccion de movimiento y compurueba si el enemigo
     * ha llegado al final del camino.
     */
    void actualizarCamino();
    
    /**
     * Devuelve un entero que codifica qué dreccion hay que seguir para moverse
     * entre 2 celdas contiguas
     * @param celda 1
     * @param celda 2
     * @return 
     *  -1 -> No se puede
     *  0 -> Arriba
     *  1 -> Derecha
     *  2 -> Abajo
     *  3 -> Izquierda
     */
    int getDirection(Celda*,Celda*);
    
    /**
     * ACTUALIZACION
     */
    
    void applyEffect(Efecto*);
    void updateEffects(float);
    void cambiaSpeed(float factor);
    
    void update();
    void render(sf::RenderTarget& target,  sf::RenderStates states);
    /**
     * AUXILIARES
     */
    bool hasArrived();
    bool isDead();
    
private:
    
    // VARIABLES DE INICIALIZACION
    // definen un tipo de enemigo
    float start_life, start_speed;
    uint start_gold, start_score, start_damage;
    
    float life, speed;
    uint gold, score, damage;
    Camino* path;
    Celda* celda;
    int celdaActual;
    int celdaDestino;
    int direction;
    bool finish;
    
    GameState* game_state;
    
    sf::Sprite sprite;
    /*********************************/
    std::vector<Efecto*> efecto;
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
                
        states.transform*=getTransform();
        
        sf::Vector2f size(80,15);
        
        sf::RectangleShape vidar(size);
        vidar.setFillColor(sf::Color(100,0,0));
        vidar.setOutlineColor(sf::Color::Black);
        vidar.setOutlineThickness(1);
        vidar.move(-size.x/2,-sprite.getTextureRect().height/2-15);
        
        sf::RectangleShape vidav(sf::Vector2f(size.x*life/start_life,size.y));
        vidav.setFillColor(sf::Color(0,100,0));
        vidav.setOutlineColor(sf::Color::Black);
        vidav.setOutlineThickness(1);
        vidav.move(-size.x/2,-sprite.getTextureRect().height/2-15);
        /*
        sf::Font font;
        if (!font.loadFromFile("resources/opensansbold.ttf"))
        {
            std::cout<<"Fuenteeeeeeeeeeeee"<<std::endl;
        }
        sf::Text text;
        text.setFont(font);
        text.setString(convertInt(life).append(" / ").append(convertInt(start_life)));
        text.setCharacterSize(15);
        text.move(-30,-sprite.getTextureRect().height/2-17);
        text.setColor(sf::Color::White);
        */
        target.draw(vidar,states);
        target.draw(vidav,states);
        //target.draw(text,states);
        target.draw(sprite, states);
        
        for(uint i=0,sz=efecto.size();i<sz;i++)
        {
            switch(efecto[i]->getType())
            {
                case Efecto::HEALTH:
                {
                    if(efecto[i]->getTimes() == -1)
                    {
                        if(efecto[i]->getDuration() == 0)
                        {
                            sf::CircleShape c(10);
                            c.setOutlineThickness(0);
                            c.setFillColor(sf::Color::Red);
                            c.setOrigin(2.5,2.5);
                            c.move(random(-10,10),random(-10,10));
                            target.draw(c,states);
                            
                            if(efecto[i]->getArea() > 0){
                                c = sf::CircleShape(efecto[i]->getArea());
                                c.setOutlineThickness(-3);
                                c.setOutlineColor(sf::Color(200,0,0,150));
                                c.setFillColor(sf::Color(255,0,0,100));
                                c.setOrigin(efecto[i]->getArea(),efecto[i]->getArea());
                                target.draw(c,states);
                            }
                        }
                        else
                        {
                            sf::RectangleShape slow;
                            slow = sf::RectangleShape(sf::Vector2f(size.x * efecto[i]->getRemainingTime() / efecto[i]->getDuration(),5));
                            slow.setFillColor(sf::Color(180,0,0));
                            slow.move(-size.x/2,-sprite.getTextureRect().height/2 - 30);
                            target.draw(slow,states);
                            break;
                        }
                    }
                    else
                    {
                       sf::RectangleShape slow;
                        slow = sf::RectangleShape(sf::Vector2f(size.x * efecto[i]->getRemainingTime() / efecto[i]->getDuration(),5));
                        slow.setFillColor(sf::Color(180,0,0));
                        slow.move(-size.x/2,-sprite.getTextureRect().height/2 - 30);
                        target.draw(slow,states);
                        break;
                    }
                    
                    break;
                }
                    
                case Efecto::SPEED:
                {
                    sf::RectangleShape slow;
                    slow = sf::RectangleShape(sf::Vector2f(size.x * efecto[i]->getRemainingTime() / efecto[i]->getDuration(),5));
                    slow.setFillColor(sf::Color(0,0,255));
                    slow.move(-size.x/2,-sprite.getTextureRect().height/2 - 22.5);
                    target.draw(slow,states);
                    break;
                }
                
                case Efecto::PATH:
                {
                    if(efecto[i]->getArea() == 0)
                    {
                        sf::RectangleShape slow;
                        slow = sf::RectangleShape(sf::Vector2f(sprite.getTextureRect().width, sprite.getTextureRect().height));
                        slow.setFillColor(sf::Color(0,255,255,180));
                        slow.move(-sprite.getTextureRect().width/2, -sprite.getTextureRect().height/2);
                        target.draw(slow,states);
                    }
                    else
                    {
                        sf::CircleShape c(efecto[i]->getArea());
                        c.setOutlineThickness(-3);
                        c.setOutlineColor(sf::Color(0,200,200,220));
                        c.setFillColor(sf::Color(0,255,255,180));
                        c.setOrigin(efecto[i]->getArea(),efecto[i]->getArea());
                        target.draw(c,states);
                    }
                    
                    break;
                }
                default:break;
            }
        }
    }
};
class EnemigoNormal : public Enemigo{
public:
    EnemigoNormal(GameState* gs, sf::Texture* t) : Enemigo(100,9,50,100,1,gs,t){
    }
};
class EnemigoRapido : public Enemigo{
public:
    EnemigoRapido(GameState* gs, sf::Texture* t) : Enemigo(50,15,25,50,2,gs,t){}
};
class EnemigoTanque : public Enemigo{
public:
    EnemigoTanque(GameState* gs, sf::Texture* t) : Enemigo(500,7,100,250,5,gs,t){}
};
#endif	/* ENEMIGO_H */