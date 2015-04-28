#ifndef STATE_CHOOSESTAGE_H
#define	STATE_CHOOSESTAGE_H
#include "State.h"
#include "State_Menu.h"

class State_ChooseStage : public State{
public:
    State_ChooseStage();
    State_ChooseStage(const State_ChooseStage& orig);
    virtual ~State_ChooseStage();
    //---------------------------
    virtual State* getNextState(Window* window);
    virtual std::string toString();
    virtual void update(Window* window, int timeU);
    virtual void render(Window* window);
    virtual void renderWithInterpolation(Window* window, State* lastState,float percent, float renderTime);
    virtual void loadResources();
    virtual bool stateChangeAlert();
private:
    int posX, posY;
    int dif;
    Texture *texFondo, *texButtons, *texButtonsS;
    Sprite *fondo;
    Sprite *sStage1, *sStage2, *sStage3, *sEasy, *sNormal, *sHard, *sBack;
    Sprite *sStage1S, *sStage2S, *sStage3S, *sEasyS, *sNormalS, *sHardS, *sBackS;
};
#endif	/* STATE_CHOOSESTAGE_H */

