#ifndef STATE_GAME_H
#define	STATE_GAME_H
#include "State.h"
#include "State_Menu.h"
#include "Nivel.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <string>
#include <SFML/Graphics.hpp>

class State_Game : public State{
public:
    State_Game();
    State_Game(const State_Game& orig);
    virtual ~State_Game();
    //---------------------------------
    virtual State* getNextState(Window* window);
    virtual std::string toString();
    virtual void update(Window* window, int timeU);
    virtual void render(Window* window);
    virtual void renderWithInterpolation(Window* window, State* lastState,float percent, float renderTime);
    virtual void loadResources();
    virtual bool stateChangeAlert();
    //---------------------------------
    void getInput(Window* window, float timeU);
protected:
private:
    View* view;
    Texture* texFondo;
    Sprite* fondo;
    int input;
    //Alberto
    float accumulator;
    float csz;
    Mapa* m;
    FactoriaEnemigo* f;
    Nivel* n;
    Torreta* t;
    GameState* game_state;
    bool rondaActiva;
    int ronda, dif, tipo;
    
    void moveView(int timeU);
};
#endif	/* STATE_GAME_H */

