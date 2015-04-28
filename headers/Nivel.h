#ifndef NIVEL_H
#define	NIVEL_H

#include "Torreta.h"
#include "State.h"
#include "FactoriaEnemigo.h"
#include "Boton.h"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include <vector>

class Nivel : public sf::Drawable, public sf::Transformable{
public:
    Nivel(char* archivo, GameState* gs);
    Nivel(const Nivel& orig);
    virtual ~Nivel();
    Nivel(int);
    void cargaRonda(int num, int dif);
    void update();
    bool creaTorreta(int,int,uint);
    Mapa* getMapa();
    std::vector<FactoriaEnemigo*> getFactorias();
private:
    Mapa* m;
    std::vector<Torreta*> torretas;
    std::vector<FactoriaEnemigo*> factorias;
    GameState game_state;
    char* archivo;
    float gold,score;
    sf::Sprite bg;
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {        
        target.draw(*m);
        for(int a=0;a<torretas.size();a++){
            target.draw(*torretas[a],states);
        }
        for(int a=0;a<factorias.size();a++){
            target.draw(*factorias[a],states);
        }
       
        sf::Font font;
        if (!font.loadFromFile("resources/opensansbold.ttf"))
        {
            std::cout<<"Fuenteeeeeeeeeeeee"<<std::endl;
        }
        
        sf::Text OroActual, ScoreActual, ActualGold, ActualScore;
        OroActual.setFont(font);
        OroActual.setString("Oro actual: ");
        OroActual.setCharacterSize(15);
        OroActual.setPosition(100,620);
        OroActual.setColor(sf::Color::Black);
        
        ActualGold.setFont(font);
        ActualGold.setString(convertInt(gold));
        ActualGold.setCharacterSize(15);
        ActualGold.setPosition(200,620);
        ActualGold.setColor(sf::Color::Black);
        
        ScoreActual.setFont(font);
        ScoreActual.setString("Puntuacion actual: ");
        ScoreActual.setCharacterSize(15);
        ScoreActual.setPosition(75,660);
        ScoreActual.setColor(sf::Color::Black);
        
        ActualScore.setFont(font);
        ActualScore.setString(convertInt(score));
        ActualScore.setCharacterSize(15);
        ActualScore.setPosition(225,660);
        ActualScore.setColor(sf::Color::Black);
       
        target.draw(bg);
        target.draw(OroActual,states);
        target.draw(ScoreActual,states);
        target.draw(ActualGold,states);
        target.draw(ActualScore,states);
        
    }
};
#endif	/* NIVEL_H */

