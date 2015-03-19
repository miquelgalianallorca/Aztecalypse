#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include "SFML.h"
#define kUpdateTimePS 1/15 //15 veces por segundo de la IA
#define kVel 120 //pixeles/segundo
using namespace std;

std::string ItoS(int num){
    std::ostringstream oss;
    oss<<num;
    return oss.str();
}

void updateGameState(int input, float elapsedTimeSinceLastCall, View *view){    
    switch(input){
    case 1:
        view->move(elapsedTimeSinceLastCall*kVel, 0);
        break;
    case 2:
        view->move(-elapsedTimeSinceLastCall*kVel, 0);
        break;
    case 3:
        view->move(0, elapsedTimeSinceLastCall*kVel);
        break;
    case 4:
        view->move(0, -elapsedTimeSinceLastCall*kVel);
        break;
    }
}

int getInput(Window *window, View *view){
    //Scroll - Teclas
    Keyboard* keyboard = new Keyboard();
    int input = keyboard->getDireccion();
    //Scroll - Raton
    Mouse* mouse = new Mouse();
    mouse->getPosition(window);
    int posX = mouse->getX();
    int posY = mouse->getY();
    if(posX < 25) input = 2;
    if(posX > (2*view->getSizeX()) - 25) input = 1;
    if(posY < 25) input = 4;
    if(posY > (2*view->getSizeY()) - 25) input = 3;
    //Eventos
    //keyboard->getEvent(*window);
    delete mouse;
    delete keyboard;
    return input;
}

void render(Window *window, View *view, Sprite *fondo){
    window->clear();
    window->setView(view);
    //Dibujar objetos
    window->draw(fondo);
    //---------------
    window->display();
}

int main(int argc, char** argv) {
    Window *window = new Window(800, 600, "Entregable - Scrolling");
    //Texturas
    Texture *texFondo = new Texture("resources/map.png");
    Sprite *fondo = new Sprite(texFondo);
    fondo->setTextureRect(0, 0, 832, 832);
    //View
    View *view = new View(350, 300, 400, 300);
    //Fisicas
    Clock *clock = new Clock();
    
    while(window->isOpen()){
        //Update
        float time = clock->getElapsedTimeAsSeconds();
        if(time > kUpdateTimePS){
            window->checkEnd(); //Para cerrar la ventana
            int input = getInput(window, view);
            updateGameState(input, time, view);
            clock->restartAsSeconds();
        }
        //Render
        render(window, view, fondo);
    }
    delete view;
    delete fondo;
    delete texFondo;
    delete window;
    delete clock;
    return 0;
}