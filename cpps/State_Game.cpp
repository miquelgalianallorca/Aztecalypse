#include "../headers/State_Game.h"
//#include "../headers/Nivel.h"
#define kVel 0.300 //pixeles/msegundo
using namespace std;

State_Game::State_Game() {
    input = 0;
    accumulator = 0.f;
    ronda = 1;
    dif = 0;
    tipo = 1;
}

State_Game::State_Game(const State_Game& orig) {
}

State_Game::~State_Game() {
    delete view;
    delete texFondo;
    delete fondo;
    delete m, f, t, n, game_state;
}
//----------------------------------------------

State* State_Game::getNextState(Window* window){
    return new State_Menu;
}

std::string State_Game::toString(){
    return "Game";
}

bool State_Game::stateChangeAlert(){
    //TO-DO
    return false;
}

void State_Game::update(Window* window, int timeU){    
    //Bucle de obtencion de eventos
    getInput(window, timeU);
    n->update();
    t->update(n->getFactorias()[0]->getEnemigos());
    if(!game_state->isPaused()){
        game_state->initPauseTime();
    }
}

void State_Game::render(Window* window){
    
    window->clear();
    window->setView(view);
    window->draw(n);
    window->draw(t);
    
    window->display();
}

void State_Game::renderWithInterpolation(Window* window, State* lastState, float percent, float renderTime){
    //float pelotaX = lastState.pelotaX*(1 - percent) + this.pelotaX*percent
    //std::cout<<"LLEGA"<<endl;
    moveView(renderTime);
    render(window);
}

void State_Game::loadResources(){
    rondaActiva = false;
    
    view = new View(1280/2, 720/2);
    view->setSize(1280, 720);
    view->setViewport(0, 0, 1, 1);
    //Texturas
    texFondo = new Texture("resources/mapaNivel1.jpg");
    fondo = new Sprite(texFondo);
    fondo->setTextureRect(0, 0, 2000, 1200);
    
    csz = 60;
    game_state = new GameState();
    n = new Nivel("somefile.xml", game_state);
    n->getMapa()->addNexo(n->getMapa()->getCell(20, 4), 50);    

    t = new Torreta12(game_state);
    t->setCelda(n->getMapa()->getCell(9,5));
    
}

void State_Game::moveView(int timeU){
    //std::cout<<"TimeU: "<<timeU<<" kVel: "<<kVel<<endl;
    int input = 0;
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            ||(sf::Keyboard::isKeyPressed(sf::Keyboard::A))) input = 2;
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            ||(sf::Keyboard::isKeyPressed(sf::Keyboard::D))) input = 1;
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            ||(sf::Keyboard::isKeyPressed(sf::Keyboard::W))) input = 4;
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            ||(sf::Keyboard::isKeyPressed(sf::Keyboard::S))) input = 3;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add)) input = 5;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract)) input = 6;
    switch(input){ //ALGO FALLA EN LAS LIMITACIONES
    case 1: //Derecha
        //if(view->getCenterX() <= (view->getSizeX()/2))
            view->move(timeU*kVel, 0);            
        break;
    case 2: //Izquierda
        //if(view->getCenterX() >= (view->getSizeX()/2))
            view->move(-timeU*kVel, 0);
        break;
    case 3: //Abajo
        //if(view->getCenterY() <= (view->getSizeY()/2))
            view->move(0, timeU*kVel);
        break;
    case 4: //Arriba
        //if(view->getCenterY() >= (view->getSizeY()/2))
            view->move(0, -timeU*kVel);
        break;
    case 5: //Mas zoom
        if((view->getSizeX()>550)){
            view->zoom(0.99f);
        }
        break;
    case 6: //Menos zoom
        if(view->getSizeX()<=1280)
            view->zoom(1.01f);
        break;       
    }
}

void State_Game::getInput(Window *window, float timeU){
    //Scroll - Raton
    /*Mouse* mouse = new Mouse();
    mouse->getPosition(window);
    int posX = mouse->getX();
    int posY = mouse->getY();
    mouse->mapPixelToCoords(posX, posY, window, view);
    posX = mouse->getPosXview();
    posY = mouse->getPosYview();
    //Esto esta pendiente de terminar
    //std::cout<<" X:"+ItoS(posX);
    //if(posX < 25){
    //    input = 2;
    //}else{
    //    if(posX > (2*view->getSizeX()) - 25) input = 1;
    //    if(posY < 25) input = 4;
    //    if(posY > (2*view->getSizeY()) - 25) input = 3;
    //}
    
    //delete mouse;
    //delete keyboard;
    //return input;
    */
    /*if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        x=sf::Mouse::getPosition(*window->getWindow()).x/csz;
        y=sf::Mouse::getPosition(*window->getWindow()).y/csz;
        cell = n->getMapa()->getCell(x,y);
        if(cell!=NULL){
            for(int i=0; i<n->getFactorias().size();i++)
                n->getFactorias()[i]->checkPaths(cell,Celda::OBSTACLE);
        }
    }
    if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
        x=sf::Mouse::getPosition(*window->getWindow()).x/csz;
        y=sf::Mouse::getPosition(*window->getWindow()).y/csz;
        n->creaTorreta(x,y);
    }*/
    
    uint x,y;
    Celda* cell;
    
    //Conversion de coordenadas
    sf::RenderWindow* w = window->getWindow();
    sf::Vector2i pixelPos = sf::Mouse::getPosition(*w);
    sf::Vector2f worldPos = w->mapPixelToCoords(pixelPos);
    x = worldPos.x / csz;
    y = worldPos.y / csz;

    //Coger teclas
    sf::Event event;
    while (w->pollEvent(event)){
        switch(event.type){
            //Si se recibe el evento de cerrar la ventana la cierro
            case sf::Event::Closed:
                window->close();
                break;
            case sf::Event::KeyPressed:
                int r=-1;
                switch(event.key.code)
                {
                    case sf::Keyboard::Y:
                        n->creaTorreta(x,y,0);
                        break;
                        
                    case sf::Keyboard::G:
                        n->creaTorreta(x,y,1);
                        break;
                        
                    case sf::Keyboard::H:
                        n->creaTorreta(x,y,2);
                        break;
                        
                    case sf::Keyboard::J:
                        n->creaTorreta(x,y, 3);
                        break;
                        
                    case sf::Keyboard::C:
                        n->creaTorreta(x,y, 4);
                        break;
                        
                    case sf::Keyboard::V:
                        n->creaTorreta(x,y, 5);
                        break;
                        
                    case sf::Keyboard::B:
                        n->creaTorreta(x,y, 6);
                        break;
                        
                    case sf::Keyboard::N:
                        n->creaTorreta(x,y, 7);
                        break;
                        
                    case sf::Keyboard::M:
                        n->creaTorreta(x,y, 8);
                        break;
                        
                    case sf::Keyboard::Comma:
                        n->creaTorreta(x,y,9);
                        break;
                }
                /*if(event.key.code==sf::Keyboard::Numpad1){
                    tipo=1;
                }else if(event.key.code==sf::Keyboard::Numpad2){
                    tipo=2;
                }else if(event.key.code==sf::Keyboard::Numpad3){
                    tipo=3;
                }
                //}else*/
                if(event.key.code==sf::Keyboard::P){
                    if(game_state->isPaused()){
                        game_state->restart();
                    }else{
                        game_state->pause();
                    }
                }else if(event.key.code==sf::Keyboard::Q){
                    float vel = game_state->getSpeed();
                    vel*=2;
                    if(vel>2.0f) vel=0.5f;
                    game_state->setSpeed(vel);
                }else if(event.key.code==sf::Keyboard::Space){
                    n->cargaRonda(ronda, dif);
                    ronda++;
                }
                if(r!=-1){
                    Enemigo::TiposEnemigo tipo;
                    switch(r){
                        case 0:
                            tipo=Enemigo::NORMAL;
                            break;
                        case 1:
                            tipo=Enemigo::RAPIDO;
                            break;
                        case 2:
                            tipo=Enemigo::TANQUE;
                            break;
                    }
                    f->createEnemy(tipo);
                }
                break;
        }
    }
    //delete cell;
}