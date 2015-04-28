#ifndef EFECTO_H
#define	EFECTO_H
#include <iostream>
#include<SFML/Graphics.hpp>
#include "config.h"
class Efecto {
public:
    enum TYPE{HEALTH,SPEED,PATH};
    Efecto(const Efecto& orig);

    
    /**
     * Constructor para efectos que se aplican una vez
     * @param tipo del efecto
     * @param valor del efecto
     * @param duracion del efecto
     * @param area del efecto
     * @param id del efecto
     */
    Efecto(TYPE, float, float, float, int);
    
    /**
     * Constructor para efectos que duran
     * @param Tipo del efecto
     * @param Valor del efecto
     * @param Numero de aplicaciones
     * @param Duracion de la aplicacion
     * @param Area del efecto
     * @param id del efecto
     */
    Efecto(TYPE, float, float, float, float, int);
    
    float getArea();
    float getValue();
    float getTimes();
    float getDuration();
    float getRemainingTime();
    uint getId();
    std::vector<uint> getCancels();
    TYPE getType();
    bool hasFinished();
    /**
     * Aplica el efecto a un enemigo
     * @param Puntero al enemigo
     * @return Si ha finalizado el efecto
     */
    void restart();
    void setCancels(std::vector<uint>);
    bool apply(float);
        
    Efecto* copy(bool);
    
    virtual ~Efecto();
private:
    sf::Clock clock;
    // Valor del efecto
    // HEALTH ----> Intervalo de vida   [-n:n]
    // SPEED -----> Cambio de velocidad [0:n]  (Mult)
    // PATH ------> Cambio de casillas  [-n:n] (Si es 0 volverá al principio)
    float value;
    // Area de aplicacion
    float area;
    // Numero de aplicaciones
    float times;
    // Duracion de la aplicacion o tiempo entre aplicaciones
    float duration, acc;
    // Variable auxiliar para que vayan bien cuando pausamos
    float lastPause;
    //Tipo
    TYPE type;
    //Finalizado
    bool finished;
    //Id del efecto
    uint id;
    //Vector de ids de efecto a los que sustituye
    std::vector<uint> ids;
};

#endif	/* EFECTO_H */