#ifndef HUD_H
#define	HUD_H
#include "SFML.h"
class HUD : public sf::Drawable {
public:
    HUD();
    HUD(const HUD& orig);
    HUD(int nivel);
    
    void update(sf::RenderWindow& window);
    void draw(sf::RenderTarget& target);
    bool checkGold(sf::RenderWindow&);
    void placeTurret(sf::RenderWindow&, sf::Mouse*,int);
    //Setters
    void setGold(float g);
    void setScore(float s);
    //Getters
    float getGold();
    float getScore();
    void getActualGold();
    void getActualScore();
    
    virtual ~HUD();
private:
    sf::Sprite torretaDMG, torretaSLOW, torretaAOE, figuraDMG, figuraSLOW, figuraAOE;
    sf::Sprite bg;
    sf::Font font;
    sf::Text actualGold, actualScore;
    float gold, score;
    float posX, posY;
    sf::Mouse *m;
    int aPintar;//1 para dmg, 2 para slow, 3 para aoe
    bool pinto=false;
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(torretaDMG);
        target.draw(torretaSLOW);
        target.draw(torretaAOE);
    }
};

#endif	/* HUD_H */