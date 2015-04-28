#ifndef GAME_H
#define	GAME_H
#include "State.h"
#include "SFML.h"

class Game {
public:
    Game();
    Game(State* pContext); //pass allocated memory
    ~Game();
    //State pattern
    void stateChanged(Window* window); //Handles the next state
    std::string getStateName();
    //-------------------------------------------
    void launch(Window* window);
protected:
    void doCleanUp();
    State* cState; //Pointer to the current state
    State *lastState;
};

#endif	/* GAME_H */