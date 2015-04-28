#include "../headers/Enemigo.h"
using namespace std;
void Enemigo::render(sf::RenderTarget& target,  sf::RenderStates states)
{
    //cout<<"Porcentaje : "<<percent<<endl;
    setPosition(interpolate(percent));
    this->draw(target,states);
}
/************************************************/
void Enemigo::applyEffect(Efecto* e) {
    
    //cout<<"Enemigo: anade efecto "<<e->getId()<<endl;
    vector<uint> cancels = e->getCancels();
    for (vector<Efecto*>::iterator it = efecto.begin(); it != efecto.end(); ){
        //cout<<" Id a comprobar "<<(*it)->getId()<<endl;
        if( contains(cancels,(*it)->getId()) ){
            delete * it;  
            it = efecto.erase(it);
            //cout<<"Enemigo: cancela efecto"<<endl;
        }else{
            ++it;
        }
    }
    efecto.push_back(e);
    //cout<<"Efectos activos: "<<efecto.size()<<endl;
}

void Enemigo::updateEffects(float gs)
{
    speed = start_speed;
    for (vector<Efecto*>::iterator it = efecto.begin(); it != efecto.end(); ){
        if( (*it)->apply(gs) ){
            //cout<<"Enemigo: recibe un efecto con valor : "<<(*it)->getValue()<<endl;
            switch((*it)->getType())
            {
                case Efecto::HEALTH:
                    life += (*it)->getValue();
                    if(life<=0){
                        if(path!=NULL){
                            path->removeUsuario(this);
                            path=NULL;
                        }
                    }
                    break;
                    
                case Efecto::PATH:
                    path = NULL;
                    celda = NULL;
                    break;
                    
                case Efecto::SPEED:
                    speed *= (*it)->getValue();
                    //cout << "La velocidad es ahora "<<speed<<endl;
                    break;
            }
        }
        if((*it)->hasFinished())
        {
            delete * it;  
            it = efecto.erase(it);
            //cout<<"Enemigo: Acaba un efecto y lo borro."<<endl;
        }
        else
        {
            ++it;
        }
        //++it;
    }
}

/************************************************/
Enemigo::Enemigo() {
}

Enemigo::Enemigo(const Enemigo& orig) {
}

Enemigo::~Enemigo(){
    //delete game_state;
    //delete celda;
    //delete path;
}


Enemigo::Enemigo(float vida, float velocidad, uint oro, uint puntuacion, uint danio, GameState* gs, sf::Texture* t){
    game_state=gs;
    
    start_life=vida;
    life=start_life;
    
    start_speed=velocidad;
    speed=start_speed;
    
    start_gold=oro;
    gold=start_gold;
    
    start_score=puntuacion;
    score=start_score;
    
    start_damage=danio;
    damage=start_damage;
    
    
    sf::Sprite enemy(*t);
    enemy.setTextureRect(sf::IntRect(0,0,32,32));
    enemy.setOrigin(16,16);
    sprite=enemy;
    
    path=NULL;
    celdaActual=-1;
    celdaDestino=-1;
    direction=-1;
    finish=false;
    celda=0;
}

Camino* Enemigo::getPath(){
    return path;
}

float Enemigo::getLife(){
    return life;
}

float Enemigo::getSpeed(){
    return speed;
}

Celda* Enemigo::getCelda(){
    return celda;
}

float Enemigo::getDamage(){
    return damage;
}

float Enemigo::getCasillasRestantes(){
    return (path!=NULL)?path->getSize()-celdaActual:1000;
}

void Enemigo::setPositionAtCell(Celda* c){
    setPosition(c->getCenter());
    Interpolacion::update(getPosition());
}

void Enemigo::setPath(Camino* camino){
    if(path!=NULL)
        path->removeUsuario(this);
    
    path=camino;
    if(path!=NULL){
        path->addUsuario(this);
        //setPosition(camino->getCell(0)->getCenter());
        celdaActual=0;
        celdaDestino=1;
        direction=getDirection(path->getCell(celdaActual),path->getCell(celdaDestino)); 
        celda=path->getCell(celdaActual);
    }
    finish=false;
}

void Enemigo::teleportToPath(Camino* camino){
    if(path!=NULL)
        path->removeUsuario(this);
    
    path=camino;
    if(path!=NULL){
        path->addUsuario(this);
        setPosition(camino->getCell(0)->getCenter());
        Interpolacion::update(getPosition());
        celdaActual=0;
        celdaDestino=1;
        direction=getDirection(path->getCell(celdaActual),path->getCell(celdaDestino)); 
        celda=path->getCell(celdaActual);
    }
    finish=false;
}

void Enemigo::setCelda(Celda* c){
    celda=c;
}

void Enemigo::cambiarDireccion(){
    sf::Vector2f c=path->getCell(celdaDestino)->getCenter();
    sf::Vector2f pos=getPosition();
    bool cambiod=false;
    switch(direction){
        case 0:
            if(pos.y <= c.y)
                cambiod= true;
            break;
        case 1:
            if(pos.x >= c.x)
                cambiod= true;
            break;
        case 2:
            if(pos.y >= c.y)
                cambiod= true;
            break;
        case 3:
            if(pos.x <= c.x)
                cambiod= true;
            break;
        default:
            cambiod= false;
    }
    if(cambiod){
        celdaDestino+=1;
        //std::cout<<"Cambio de Direccion:"<<celdaDestino<<std::endl;
        direction=getDirection(path->getCell(celdaDestino-1),path->getCell(celdaDestino)); 
    }
}

void Enemigo::cambiarCelda(){
    sf::Vector2f c=path->getCell(celdaActual)->getCenter();
    sf::Vector2f pos=getPosition();
    float r=path->getCell(celdaActual)->getSize().x/2;
    bool cambioc=false;
    switch(direction){
        case 0:
            if(pos.y <= c.y - r)
                cambioc= true;
            break;
        case 1:
            if(pos.x >= c.x + r)
                cambioc= true;
            break;
        case 2:
            if(pos.y >= c.y + r)
                cambioc= true;
            break;
        case 3:
            if(pos.x <= c.x - r)
                cambioc= true;
            break;
        default:
            cambioc= false;
    }
    if(cambioc){
        celdaActual+=1;
        celda=path->getCell(celdaActual);
        //std::cout<<"Cambio de celda:"<<celdaActual<<std::endl;
    }
}

void Enemigo::actualizarCamino(){
    if(!finish && path!=NULL){
        cambiarCelda();
        cambiarDireccion();
        
        if(celdaActual==path->getSize()-1){
            finish=true;
            path->removeUsuario(this);
            //std::cout<<"GET BACKDOORED BTCH."<<std::endl;
        }
    }
}

int Enemigo::getDirection(Celda* c1, Celda* c2){
    /* 1-arriba 2-Derecha 3-Abajo 4-Izquierda*/
    if(c1->getLPos().x>c2->getLPos().x)
        return 3;
    else if(c1->getLPos().x<c2->getLPos().x)
        return 1;
    else if(c1->getLPos().y>c2->getLPos().y)
        return 0;
    else if(c1->getLPos().y<c2->getLPos().y)
        return 2;
    else return -1;
}

void Enemigo::update(){
    bool pause=game_state->isPaused();
    float pause_time = game_state->getPauseTime();
    float gs=game_state->getSpeed();
    
    if(!pause){
        if(pause_time > 0){
            cout<<"El juego ha sido pausado "<<pause_time<<endl;
            for(int i = 0, sz = efecto.size(); i < sz ; i++){
                efecto[i]->restart();
            }
        }
        updateEffects(gs);
    }
    
    if(!pause && !finish && path!=NULL){
        actualizarCamino();
        sf::Vector2f interval(0,0);
        float s=speed*gs;
        switch(direction){
            case 0:
                interval.y-=s;
                break;
            case 1:
                interval.x+=s;
                break;
            case 2:
                interval.y+=s;
                break;
            case 3:
                interval.x-=s;
                break;
            default:
                break;
        }
        sf::Transformable::move(interval);
        Interpolacion::update(getPosition());
    }
    
}

bool Enemigo::hasArrived(){
    return finish;
}

bool Enemigo::isDead(){
    return life<=0;
}

//variable=(condicion)?valor si true:valor si false;