#include "../headers/Boton.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

Boton::Boton(GameState* gs, int tipo) {
    state = gs;
    sf::Texture *tex=new sf::Texture();
    if (!tex->loadFromFile("resources/botones.png"))
    {
        exit(0);
    }
    sf::Sprite bot(*tex);
    switch(tipo){
        case 1: bot.setTextureRect(sf::IntRect(2,2,53,40));
                bot.setOrigin(27,20);  
                bot.setPosition(120,650);
                factor = 1.0f;
                iniY = 2;
                break;
        case 2: bot.setTextureRect(sf::IntRect(2,86,53,126));
                bot.setOrigin(27,20);  
                bot.setPosition(180,650);
                factor = 2.0f;
                iniY = 86;
                break;
        case 3: bot.setTextureRect(sf::IntRect(2,170,53,210));
                bot.setOrigin(27,20);  
                bot.setPosition(60,650);
                factor = 0.5f;
                iniY = 170;
                break;
    }    
    sp=bot;
}

Boton::Boton(const Boton& orig) {
}

Boton::~Boton() {
}

void Boton::update(sf::RenderWindow& window){
    sf::Mouse *m = new sf::Mouse();
    m->getPosition(window);
    int posX = m->getPosition(window).x;
    int posY = m->getPosition(window).y;
    
    if(sp.getGlobalBounds().contains(posX,posY) || factor==state->getSpeed()){
        sp.setTextureRect(sf::IntRect(2,iniY+42,53,40));
        if(m->isButtonPressed(sf::Mouse::Left))
            state->setSpeed(factor);
    }        
    else{
        sp.setTextureRect(sf::IntRect(2,iniY,53,40));
    }
    delete m;
}