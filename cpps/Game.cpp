#include "../headers/Game.h"
#define kUpdateTimePS 1/15 //15 veces por segundo de la IA

Game::Game() {
}
Game::Game(State* pContext) {
    cState = pContext;
}
Game::~Game(){
    delete cState;
    delete lastState;
}

//---------------------------------

// Handles the state change
void Game::stateChanged(Window* window){
    if(cState){
        State* pState = cState->getNextState(window);
        delete cState;
        cState = pState;
    }
}

std::string Game::getStateName(){
    std::string s = cState->toString();
    return s;
}

//---------------------------------

void Game::launch(Window* window){
    float ia = 1000/15;
    sf::Clock updateClock, renderClock;
    int updateTime = 0;
    int renderTime = 0;
    cState->loadResources();
    updateTime = updateClock.getElapsedTime().asMilliseconds();
    while(window->isOpen()){
        if(updateClock.getElapsedTime().asMilliseconds() > ia){
            lastState = cState;
            updateTime = updateClock.restart().asMilliseconds();
            cState->update(window, updateTime);
            if(cState->stateChangeAlert()){
                stateChanged(window);
                cState->loadResources();
            }
        }
        percent = std::min(1.f, updateClock.getElapsedTime().asMilliseconds()/ia);
        renderTime = renderClock.restart().asMilliseconds();
        cState->renderWithInterpolation(window, lastState, percent, renderTime);
    }
}