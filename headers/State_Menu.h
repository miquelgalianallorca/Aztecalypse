#ifndef STATE_MENU_H
#define	STATE_MENU_H
#include "State.h"
#include "State_Game.h"
#include "State_ChooseStage.h"
#include "SFML.h"

class State_Menu : public State{
public:
    State_Menu();
    State_Menu(const State_Menu& orig);
    virtual ~State_Menu();
    //---------------------------------
    /*void execute(Window *window);
    void render(Window *window, int x, int y);*/
    //---------------------------------
    virtual State* getNextState(Window* window);
    virtual std::string toString();
    virtual void update(Window* window, int timeU);
    virtual void render(Window* window);
    virtual void renderWithInterpolation(Window* window, State* lastState,float percent, float renderTime);
    virtual void loadResources();
    virtual bool stateChangeAlert();
private:
    int posX, posY;
    Texture *texFondo, *texMenu, *texMenuS;
    Sprite *fondo, *menuPlay, *menuOptions, *menuSalir;
    Sprite *menuPlayS, *menuOptionsS, *menuSalirS;
    Mouse* m;
};
#endif	/* STATE_MENU_H */

