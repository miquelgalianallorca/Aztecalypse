#include "../headers/State_Menu.h"
using namespace std;

State_Menu::State_Menu() {
    posX = posY = 0;
    m = new Mouse();
}

State_Menu::State_Menu(const State_Menu& orig) {
}

State_Menu::~State_Menu(){
    delete fondo;
    delete texFondo, texMenu;
    delete menuPlay, menuOptions, menuSalir;
    delete menuPlayS, menuOptionsS, menuSalirS;
    delete m;
}

//----------------------------------------------

State* State_Menu::getNextState(Window* window){
    if(nextState == 0){
        window->close();
    }
    if(nextState == 1){
        State_ChooseStage* sg = new State_ChooseStage();
        return sg;
    }
    return new State_Menu;
}

std::string State_Menu::toString(){
    return "Menu";
}

void State_Menu::update(Window* window, int timeU){
    m->getPosition(window);
    posX = m->getX();
    posY = m->getY();
    //std::cout<<"X: "<<posX<<" Y: "<<posY<<endl;
}

bool State_Menu::stateChangeAlert(){
    //Mouse* m = new Mouse();
    bool change = false;
    if(menuPlay->getHover(posX, posY) && m->isLeftClickPressed()){
        nextState = 1;
        change = true;
    }
    if(menuSalir->getHover(posX, posY) && m->isLeftClickPressed()){
        nextState = 0;
        change = true;
    }
    //delete m;
    return change;
    //return false;
}

void State_Menu::render(Window* window){
    window->clear();
    window->draw(fondo);
    if(menuPlay->getHover(posX,posY)) window->draw(menuPlayS);
    else window->draw(menuPlay);
    if(menuOptions->getHover(posX,posY)) window->draw(menuOptionsS);
    else window->draw(menuOptions);
    if(menuSalir->getHover(posX,posY)) window->draw(menuSalirS);
    else window->draw(menuSalir);
    window->display();
}

void State_Menu::renderWithInterpolation(Window* window, State* lastState,float percent, float renderTime){
    render(window);
}

void State_Menu::loadResources(){
    //Fondo
    texFondo = new Texture("resources/fondoMenu.png");
    fondo = new Sprite(texFondo);
    fondo->setTextureRect(0, 0, 2000, 1200);
    fondo->setPosition(0,0);
    //Botones naranja
    texMenu = new Texture("resources/botonesMenuNaranja.png");
    menuPlay = new Sprite(texMenu);
    menuPlay->setTextureRect(0, 0, 318, 81);
    menuPlay->setPosition((1280/2)-(318/2), (800/2)-(81/2));
    menuOptions = new Sprite(texMenu);
    menuOptions->setTextureRect(0, 81, 318, 81);
    menuOptions->setPosition((1280/2)-(318/2), (800/2)-(81/2)+81+5);
    menuSalir = new Sprite(texMenu);
    menuSalir->setTextureRect(0, 81*2, 318, 81);
    menuSalir->setPosition((1280/2)-(318/2), (800/2)-(81/2)+(81*2)+(5*2));
    //Botones rojo
    texMenuS = new Texture("resources/botonesMenuRojo.png");
    menuPlayS = new Sprite(texMenuS);
    menuPlayS->setTextureRect(0, 0, 318, 81);
    menuPlayS->setPosition((1280/2)-(318/2), (800/2)-(81/2));
    menuOptionsS = new Sprite(texMenuS);
    menuOptionsS->setTextureRect(0, 81, 318, 81);
    menuOptionsS->setPosition((1280/2)-(318/2), (800/2)-(81/2)+81+5);
    menuSalirS = new Sprite(texMenuS);
    menuSalirS->setTextureRect(0, 81*2, 318, 81);
    menuSalirS->setPosition((1280/2)-(318/2), (800/2)-(81/2)+(81*2)+(5*2));
}