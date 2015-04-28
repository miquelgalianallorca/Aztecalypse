#include "../headers/State_ChooseStage.h"

State_ChooseStage::State_ChooseStage() {
}

State_ChooseStage::State_ChooseStage(const State_ChooseStage& orig) {
}

State_ChooseStage::~State_ChooseStage(){
    delete texFondo, texButtons, texButtonsS;
    delete fondo;
    delete sStage1, sStage2, sStage3, sEasy, sNormal, sHard, sBack;
    delete sStage1S, sStage2S, sStage3S, sEasyS, sNormalS, sHardS, sBackS;
}

//------------------------------------------------------------------

State* State_ChooseStage::getNextState(Window* window){
    if(nextState == 1) return new State_Menu;
    if(nextState == 2) return new State_Game;
    return new State_Menu;
}

std::string State_ChooseStage::toString(){
    return "ChooseStage";
}

bool State_ChooseStage::stateChangeAlert(){
    Mouse* m = new Mouse();
    bool change = false;
    if(sBack->getHover(posX, posY) && m->isLeftClickPressed()){
        nextState = 1;
        change = true;
    }
    if(sEasy->getHover(posX,posY) && m->isLeftClickPressed()){
        nextState = 2;
        dif = 1;
        change = true;
    }
    if(sNormal->getHover(posX,posY) && m->isLeftClickPressed()){
        nextState = 2;
        dif = 2;
        change = true;
    }
    if(sHard->getHover(posX,posY) && m->isLeftClickPressed()){
        nextState = 2;
        dif = 3;
        change = true;
    }
    delete m;
    return change;
}

//------------------------------------------------------------------

void State_ChooseStage::update(Window* window, int timeU){
    Mouse *m = new Mouse();
    m->getPosition(window);
    posX = m->getX();
    posY = m->getY();
    delete m;
}

void State_ChooseStage::render(Window* window){
    window->clear();
    window->draw(fondo);
    if(sStage1->getHover(posX,posY)) window->draw(sStage1S);
    else window->draw(sStage1);
    if(sStage2->getHover(posX,posY)) window->draw(sStage2S);
    else window->draw(sStage2);
    if(sStage3->getHover(posX,posY)) window->draw(sStage3S);
    else window->draw(sStage3); 
    if(sEasy->getHover(posX,posY)) window->draw(sEasyS);
    else window->draw(sEasy);
    if(sNormal->getHover(posX,posY)) window->draw(sNormalS);
    else window->draw(sNormal);
    if(sHard->getHover(posX,posY)) window->draw(sHardS);
    else window->draw(sHard);
    if(sBack->getHover(posX,posY)) window->draw(sBackS);
    else window->draw(sBack);
    //---------------
    window->display();
}

void State_ChooseStage::renderWithInterpolation(Window* window, State* lastState,float percent, float renderTime){
    render(window);
}

void State_ChooseStage::loadResources(){
    //view = new View(350, 300, 1280/2, 720/2);
    //Texturas
    texFondo = new Texture("resources/fondoSeleccionNivel.png");
    fondo = new Sprite(texFondo);
    fondo->setTextureRect(0, 0, 2000, 1200);
    //---------------------------------------------
    texButtons = new Texture("resources/botonesSelNivelNaranja.png");
    sStage1 = new Sprite(texButtons);
    sStage1->setTextureRect(0,0,318,81);
    sStage1->setPosition((1280/2)+300, (800/2));
    sStage2 = new Sprite(texButtons);
    sStage2->setTextureRect(0,81,318,81);
    sStage2->setPosition(500, 80);
    sStage3 = new Sprite(texButtons);
    sStage3->setTextureRect(0,81*2,318,81);
    sStage3->setPosition(80, 500);
    sEasy = new Sprite(texButtons);
    sEasy->setTextureRect(0,81*3,64,64);
    sEasy->setPosition(1020,408);
    sNormal = new Sprite(texButtons);
    sNormal->setTextureRect(64,81*3,64,64);
    sNormal->setPosition(1100,408);
    sHard = new Sprite(texButtons);
    sHard->setTextureRect(64*2,81*3,64,64);
    sHard->setPosition(1180,408);
    sBack = new Sprite(texButtons);
    sBack->setTextureRect(64*3,81*3,74,74);
    sBack->setPosition(1280-64-20,0+10);
    //--------------------------------------------
    texButtonsS = new Texture("resources/botonesSelNivelRojo.png");
    sStage1S = new Sprite(texButtonsS);
    sStage1S->setTextureRect(0,0,318,81);
    sStage1S->setPosition((1280/2)+300, (800/2));
    sStage2S = new Sprite(texButtonsS);
    sStage2S->setTextureRect(0,81,318,81);
    sStage2S->setPosition(500, 80);
    sStage3S = new Sprite(texButtonsS);
    sStage3S->setTextureRect(0,81*2,318,81);
    sStage3S->setPosition(80, 500);
    sEasyS = new Sprite(texButtonsS);
    sEasyS->setTextureRect(0,81*3,64,64);
    sEasyS->setPosition(1020,408);
    sNormalS = new Sprite(texButtonsS);
    sNormalS->setTextureRect(64,81*3,64,64);
    sNormalS->setPosition(1100,408);
    sHardS = new Sprite(texButtonsS);
    sHardS->setTextureRect(64*2,81*3,64,64);
    sHardS->setPosition(1180,408);
    sBackS = new Sprite(texButtonsS);
    sBackS->setTextureRect(64*3,81*3,74,74);
    sBackS->setPosition(1280-64-20,0+10);
}