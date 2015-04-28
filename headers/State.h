#ifndef STATE_H
#define	STATE_H
#include "SFML.h"

class State {
public:
    //-------------------------- Patron State
    virtual State* getNextState(Window* window) = 0;
    virtual std::string toString() = 0;
    virtual void update(Window* window, int timeU) = 0;
    virtual void render(Window* window) = 0;
    virtual void renderWithInterpolation(Window* window, State* lastState,float percent, float renderTime) = 0;
    virtual void loadResources() = 0;
    virtual bool stateChangeAlert() = 0;
protected:
    int nextState;
};
#endif	/* STATE_H */