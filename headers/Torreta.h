#ifndef TORRETA_H
#define	TORRETA_H

#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Enemigo.h"
#include "GameState.h"
#include "config.h"
#include "Efecto.h"
class Celda;

/*Changelog
 * Anyadida la variable iniRate donde guardar la v de disparo inicial
 * 
 * Anyadido el metodo cambiaCadencia para cambiar la v de disparo
 *  segun la velocidad del juego 
 */

class Torreta : public sf::Drawable, public sf::Transformable {
public:
    
    enum Focus{MORE_DAMAGE,WEAKER,TANK,FASTEST,NEAR_NEXO};
    
    /**
     * CONSTRUCTORES
     */
    
    Torreta();
    Torreta(const Torreta& orig);
    /*******************************************************************************************/
    Torreta(uint rang, float rf, vector<Efecto*> e, uint pric, uint repai, GameState* gs);
    /*******************************************************************************************/
    
    /**
     * GETTERS
     */
    
    Celda* getCelda();
    
    /**
     * SETTERS
     */
    
    void setCelda(Celda*);
    
    /**
     * DETECCION DE ENEMIGOS
     */
    
    /**
     * Devuelve los enemigos afectados por un disparo de la torreta
     * @param Enemigos del mapa
     * @return vector con los enemigos afectados
     */
    void detect(std::vector<Enemigo*>);
    
    /**
     * Devuelve el enemigo objetivo del disparo de la torreta
     * @param Enemigos al alcance de la torreta
     * @return Enemigo que será disparado
     */
    Enemigo* choose(std::vector<Enemigo*>);
    
    /**
     * Aplica los efectos de la Torreta a enemigos
     * @param Enemigos afectados
     */
    void shoot(std::vector<Enemigo*>);
    void update(std::vector<Enemigo*>);
    
    virtual ~Torreta();
private:
    // VARIABLES DE INSTANCIA
    // pueden ser modificadas en ejecucion
    uint range, price, repair;
    float rateOfFire, lastPauseTime;
    
    GameState* game_state;
    
    /**************************/
    std::vector<Efecto*> efecto;
    bool first_attack;
    /**************************/
    
    Focus focus;
    sf::Sprite sprite;
    Enemigo* target;
    Celda* celda;
    
    sf::Clock reloj;
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform*=getTransform();
        
        //Dibujo el rango
        sf::CircleShape c(range);
        c.setOutlineThickness(-3);
        
        if(this->target==NULL){
            c.setOutlineColor(sf::Color(0,0,0,200));
        }else{
            c.setOutlineColor(sf::Color(200,0,0,200));
            int s=distancev(this->target->getPosition(),getPosition());
            
            sf::RectangleShape r(sf::Vector2f(3,s));
            r.setFillColor(sf::Color(255,0,0,200));
            r.rotate(0);
            target.draw(r,states);
        }
        
        c.setFillColor(sf::Color::Transparent);
        c.setOrigin(range,range);
        target.draw(c,states);
        
        target.draw(sprite, states);
    }
    /**
     * Calcula si un enemigo está en el rango de la torreta
     * @param Enemigo
     * @return True si está en el rango, false si no
     */
    bool inRange(Enemigo*);
};

class TorretaBase : public Torreta{
public:
    TorretaBase(GameState* gs) : Torreta(150,0.5,getEffects(),100,80,gs){}
    
    vector<Efecto*> getEffects()
    {    
        vector<Efecto*> e;
        vector<uint> cancels;
        Efecto* ef;

        //Damage
        ef = new Efecto(Efecto::HEALTH, 0, 0, 0, 1);
        cancels.push_back(1);
        ef->setCancels(cancels);
        e.push_back(ef);
        cancels.clear();
        return e;
    }
};

class Torreta1 : public Torreta{
public:
    Torreta1(GameState* gs) : Torreta(250,0.3,getEffects(),100,80,gs){}
    
    vector<Efecto*> getEffects()
    {    
        vector<Efecto*> e;
        vector<uint> cancels;
        Efecto* ef;

        //Damage
        ef = new Efecto(Efecto::HEALTH, -30, 0, 0, 1);
        ef->setCancels(cancels);
        e.push_back(ef);
        
        return e;
    }
};

class Torreta11 : public Torreta{
public:
    Torreta11(GameState* gs) : Torreta(500,2,getEffects(),100,80,gs){}
    
    vector<Efecto*> getEffects()
    {    
        vector<Efecto*> e;
        vector<uint> cancels;
        Efecto* ef;

        //Damage
        ef = new Efecto(Efecto::HEALTH, -100, 0, 0, 1);
        ef->setCancels(cancels);
        e.push_back(ef);
        
        return e;
    }
};

class Torreta12 : public Torreta{
public:
    Torreta12(GameState* gs) : Torreta(200,3,getEffects(),100,80,gs){}
    
    vector<Efecto*> getEffects()
    {    
        vector<Efecto*> e;
        vector<uint> cancels;
        Efecto* ef;

        //Damage
        
        ef = new Efecto(Efecto::HEALTH, -1.2, 3,0, 1);
        cancels.push_back(1);
        ef->setCancels(cancels);
        e.push_back(ef);
        
        return e;
    }
};

class Torreta2 : public Torreta{
public:
    Torreta2(GameState* gs) : Torreta(200,3,getEffects(),100,80,gs){}
    
    vector<Efecto*> getEffects()
    {    
        vector<Efecto*> e;
        vector<uint> cancels;
        Efecto* ef;

        
        ef = new Efecto(Efecto::SPEED,0.4,1,50, 2);
        cancels.push_back(2);
        ef->setCancels(cancels);
        e.push_back(ef);
        
        return e;
    }
};

class Torreta21 : public Torreta{
public:
    Torreta21(GameState* gs) : Torreta(250,5,getEffects(),100,80,gs){}
    
    vector<Efecto*> getEffects()
    {    
        vector<Efecto*> e;
        vector<uint> cancels;
        Efecto* ef;
        
        ef = new Efecto(Efecto::PATH,0,0,0, 2);
        //cancels.push_back(2);
        ef->setCancels(cancels);
        e.push_back(ef);
        
        ef = new Efecto(Efecto::SPEED,0,3,100, 3);
        cancels.push_back(3);
        ef->setCancels(cancels);
        e.push_back(ef);
        return e;
    }
};

class Torreta22 : public Torreta{
public:
    Torreta22(GameState* gs) : Torreta(300,5,getEffects(),100,80,gs){}
    
    vector<Efecto*> getEffects()
    {    
        vector<Efecto*> e;
        vector<uint> cancels;
        Efecto* ef;
        
        ef = new Efecto(Efecto::HEALTH, -10, 5, 1,150,1 );
        cancels.push_back(1);
        ef->setCancels(cancels);
        e.push_back(ef);
        cancels.clear();
        
        ef = new Efecto(Efecto::SPEED,0.5,3,150, 3);
        cancels.push_back(3);
        ef->setCancels(cancels);
        e.push_back(ef);
        return e;
    }
};

class Torreta3 : public Torreta{
public:
    Torreta3(GameState* gs) : Torreta(150,5,getEffects(),100,80,gs){}
    
    vector<Efecto*> getEffects()
    {    
        vector<Efecto*> e;
        vector<uint> cancels;
        Efecto* ef;
        
        ef = new Efecto(Efecto::HEALTH,-15,0,40, 2);
        ef->setCancels(cancels);
        e.push_back(ef);
        return e;
    }
};

class Torreta31 : public Torreta{
public:
    Torreta31(GameState* gs) : Torreta(300,5,getEffects(),100,80,gs){}
    
    vector<Efecto*> getEffects()
    {    
        vector<Efecto*> e;
        vector<uint> cancels;
        Efecto* ef;
        
        ef = new Efecto(Efecto::HEALTH, -30, 5, 0.7,150,1 );
        cancels.push_back(1);
        ef->setCancels(cancels);
        e.push_back(ef);
        cancels.clear();
        
        ef = new Efecto(Efecto::HEALTH,-20,0,150, 2);
        cancels.push_back(2);
        ef->setCancels(cancels);
        e.push_back(ef);
        cancels.clear();
        
        ef = new Efecto(Efecto::SPEED,0,1,0, 3);
        cancels.push_back(3);
        ef->setCancels(cancels);
        e.push_back(ef);

        return e;
    }
};

class Torreta32 : public Torreta{
public:
    Torreta32(GameState* gs) : Torreta(300,1,getEffects(),100,80,gs){}
    
    vector<Efecto*> getEffects()
    {    
        vector<Efecto*> e;
        vector<uint> cancels;
        Efecto* ef;
        
        ef = new Efecto(Efecto::HEALTH,-20,0,250, 2);
        ef->setCancels(cancels);
        e.push_back(ef);
        
        return e;
    }
};
#endif	/* TORRETA_H */

