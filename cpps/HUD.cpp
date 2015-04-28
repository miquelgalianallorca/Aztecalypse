#include "../headers/HUD.h"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;
HUD::HUD(){
}
HUD::HUD(const HUD& orig){
}
HUD::HUD(int nivel){
    
    m = new sf::Mouse();
    
    sf::Texture *tex=new sf::Texture();
    if (!tex->loadFromFile("resources/buttons.png"))
    {
        std::cerr << "Error cargando la imagen buttons.png";
        exit(0);
    }
    sf::Sprite t1(*tex);
    sf::Sprite t2(*tex);
    sf::Sprite t3(*tex);
    sf::Sprite f1(*tex);
    sf::Sprite f2(*tex);
    sf::Sprite f3(*tex);
    
    t1.scale(0.7,0.7);
    t1.setTextureRect(sf::IntRect(0,0,128,128));
    t1.setOrigin(64,64);
    t1.setPosition(1000,670);
    torretaDMG = t1;
    
    t2.scale(0.7,0.7);
    t2.setTextureRect(sf::IntRect(0,128,128,128));
    t2.setOrigin(64,64);
    t2.setPosition(1138,670);
    torretaSLOW = t2;
    
    t3.scale(0.7,0.7);
    t3.setTextureRect(sf::IntRect(0,256,128,128));
    t3.setOrigin(64,64);
    t3.setPosition(1266,670);
    torretaAOE = t3;
    
    //HACER SPRITES PNG TRANSPARENTES DE POR SI
    f1.scale(0.7,0.7);
    f1.setTextureRect(sf::IntRect(0,0,128,128));
    f1.setOrigin(64,64);
    figuraDMG = f1;
    
    f2.scale(0.7,0.7);
    f2.setTextureRect(sf::IntRect(0,0,128,128));
    f2.setOrigin(64,64);
    figuraSLOW = f2;
    
    f2.scale(0.7,0.7);
    f2.setTextureRect(sf::IntRect(0,0,128,128));
    f2.setOrigin(64,64);
    figuraAOE = f3;
    
    sf::Texture *im=new sf::Texture();
    if (!im->loadFromFile("resources/hud.png"))
    {
        std::cerr << "Error cargando la imagen hud.png";
        exit(0);
    }
    sf::Sprite b(*im);
    b.setTextureRect(sf::IntRect(0,0,1280,120));
    b.setPosition(0,600);
    bg=b;
    
    if(!font.loadFromFile("resources/opensansbold.ttf"))
    {
        std::cerr << "Error cargando la fuente";
        exit(0);
    }
    actualGold.setFont(font);
    actualGold.setCharacterSize(30);
    actualGold.setColor(sf::Color(0, 0, 70));
    actualGold.setPosition(100,650);
    actualGold.setString("0");
    actualScore.setFont(font);
    actualScore.setCharacterSize(30);
    actualScore.setColor(sf::Color(0, 0, 70));
    actualScore.setPosition(200,650);
    actualScore.setString("0");
    
    
    
    gold=87;
    score=9000;
    aPintar=0;
    
    
        
}
void HUD::placeTurret(sf::RenderWindow& w, sf::Mouse* m,int x){

    switch(x){
    case 1:
        aPintar=1;
        break;
    case 2:
        aPintar=2;
        break;
    case 3:
        aPintar=3;
        break;
    default:
        aPintar=0;
        break;
        }
}

void HUD::update(sf::RenderWindow& window){
    m->getPosition(window);
    posX = m->getPosition(window).x;
    posY = m->getPosition(window).y;
   if((m->isButtonPressed(sf::Mouse::Left) || m->isButtonPressed(sf::Mouse::Right)) && pinto){
        
    } 
    if(gold>=50){
        torretaAOE.setTextureRect(sf::IntRect(0,0,128,128));
        torretaDMG.setTextureRect(sf::IntRect(0,0,128,128));
        torretaSLOW.setTextureRect(sf::IntRect(0,0,128,128));
        //comprobamos el efecto hover
        if(torretaDMG.getGlobalBounds().contains(posX,posY)){
            torretaDMG.setTextureRect(sf::IntRect(128,0,128,128));
            if(m->isButtonPressed(sf::Mouse::Left)){
                placeTurret(window,m,1);
            }
        }else if(torretaSLOW.getGlobalBounds().contains(posX,posY)){
             torretaSLOW.setTextureRect(sf::IntRect(128,0,128,128));
             if(m->isButtonPressed(sf::Mouse::Left)){
                 placeTurret(window,m,2);
            }
        }else if(torretaAOE.getGlobalBounds().contains(posX,posY)){
                torretaAOE.setTextureRect(sf::IntRect(128,0,128,128));
                if(m->isButtonPressed(sf::Mouse::Left)){
                    placeTurret(window,m,3);
            }
        }
    }else{
        torretaAOE.setTextureRect(sf::IntRect(256,0,128,128));
        torretaDMG.setTextureRect(sf::IntRect(256,0,128,128));
        torretaSLOW.setTextureRect(sf::IntRect(256,0,128,128)); 
    }
}
void HUD::draw(sf::RenderTarget& target){
   
           
    target.draw(bg);
    target.draw(torretaDMG);
    target.draw(torretaSLOW);
    target.draw(torretaAOE);
    if(pinto){
        switch(aPintar){
        case 0:
            break;
        case 1:
            figuraDMG.setPosition(posX,posY);
            target.draw(figuraDMG);
            break;
        case 2:

            figuraSLOW.setPosition(posX,posY);
            target.draw(figuraSLOW);
            break;
        case 3:
            figuraAOE.setPosition(posX,posY);
            target.draw(figuraAOE);
            break;
        }
    }
}
bool HUD::checkGold(sf::RenderWindow& window){
    if(gold>50){
        return true;
    }else{
        return false;
    } 
}
//Setters
void HUD::setScore(float s){
    std::ostringstream string;
    string << s;
    actualScore.setString("Puntuacion: " + string.str());
}
void HUD::setGold(float g){
    std::ostringstream string;
    string << g;
    actualGold.setString("Oro: " + string.str());
}
//Getters
float HUD::getScore(){
    return score;
}
float HUD::getGold(){
    return gold;
}
/*void HUD::getActualGold(){
    actualGold.setString("Oro: "+actualGold);
}
void HUD::getActualScore(){
    actualScore.setString("Score: "+actualScore);
}*/
HUD::~HUD(){
}

