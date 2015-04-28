#include "../headers/Torreta.h"
#include "../headers/Celda.h"
using namespace std;

Torreta::Torreta() {
}

Torreta::Torreta(const Torreta& orig) {
}

Torreta::Torreta(uint rang, float rf, vector<Efecto*> e, uint pric, uint repai, GameState* gs){
    range=rang;
    rateOfFire=rf;
    efecto=e;
    price=pric;
    repair=repai;
    game_state=gs;
    
    focus=Torreta::NEAR_NEXO;
    
    lastPauseTime=0;
    first_attack = true;
    target=0;
    sf::Texture *txt=new sf::Texture();
    if (!txt->loadFromFile("resources/turret.png"))
    {
        std::cerr << "Error cargando la imagen orc.png";
        exit(0);
    }
    sf::Sprite sp(*txt);
    sp.scale(0.4,0.4);
    sp.setTextureRect(sf::IntRect(0,0,128,128));
    sp.setOrigin(64,64);
    sprite=sp;
}

Celda* Torreta::getCelda(){
    return celda;
}

void Torreta::setCelda(Celda* c){
    celda=c;
    setPosition(c->getCenter());
    celda->setState(Celda::TOWER);
}

void Torreta::update(vector<Enemigo*> e){
    if(!game_state->isPaused()){
        shoot(e);
    }
}

void Torreta::detect(vector<Enemigo*> e){
    target=choose(e);
    int a = 0;
    if(target!=NULL){
        /**************************************************************/
        float area;
        for(uint i=0,sz=efecto.size(); i<sz ;i++){
            area = efecto[i]->getArea();
            if(area > 0){// Aplico el efecto al target y a todos
                for(uint j=0,sz=e.size();j<sz;j++){
                    if(distancev(e[j]->getPosition(),target->getPosition())<area){
                        if(e[j]!=NULL && e[j]!=target)
                        {
                            a++;
                            e[j]->applyEffect(efecto[i]->copy(false));
                        }
                    }
                }
            }
            target->applyEffect(efecto[i]->copy(true));
            first_attack = false;
        }
        /**************************************************************************/
        
    }
}

Enemigo* Torreta::choose(vector<Enemigo*> e){
    Enemigo* aux=NULL;
    int n,l;
    for(uint i=0,sz=e.size();i<sz;i++){
        if(e[i]!=NULL && inRange(e[i])){
            if(aux==NULL){
                aux=e[i];
            }else{
                switch(focus){
                    case Torreta::NEAR_NEXO:
                        n=e[i]->getCasillasRestantes();
                        l=(aux!=NULL)?aux->getCasillasRestantes():1000;
                        if(n<l){
                            aux=e[i];
                        }else if(n==l && target!=NULL && e[i]==target){
                            aux=target;
                        }
                        break;
                        
                    case Torreta::FASTEST:
                        n=e[i]->getSpeed();
                        l=(aux!=NULL)?aux->getSpeed():0;
                        if(n>l){
                            aux=e[i];
                        }else if(n==l && target!=NULL && e[i]==target){
                            aux=target;
                        }
                        break;
                        
                    case Torreta::MORE_DAMAGE:
                        n=e[i]->getDamage();
                        l=(aux!=NULL)?aux->getDamage():0;
                        if(n>l){
                            aux=e[i];
                        }else if(n==l && target!=NULL && e[i]==target){
                            aux=target;
                        }
                        break;
                        
                    case Torreta::WEAKER:
                        n=e[i]->getLife();
                        l=(aux!=NULL)?aux->getLife():100000;
                        if(n<l){
                            aux=e[i];
                        }else if(n==l && target!=NULL && e[i]==target){
                            aux=target;
                        }
                        break;
                        
                    case Torreta::TANK:
                        n=e[i]->getLife();
                        l=(aux!=NULL)?aux->getLife():100000;
                        if(n>l){
                            aux=e[i];
                        }else if(n==l && target!=NULL && e[i]==target){
                            aux=target;
                        }
                        break;
                        
                    default:
                        break;
                }
            }
        }
    }
    return aux;
}

void Torreta::shoot(vector<Enemigo*> e){
    
    target=choose(e);
    if(target!=NULL)
        setRotation(-65-toDegrees(angle(target->getPosition(),getPosition())));
    
    bool disparo=false;
    float inc=reloj.getElapsedTime().asSeconds();
    float gs=game_state->getSpeed();
    
    if(game_state->wasPaused()){
        lastPauseTime=game_state->getPauseTime();
    }
    
    if(lastPauseTime!=0 && (inc-lastPauseTime) >= rateOfFire / gs){
        disparo=true;
        lastPauseTime=0;
    }else if( lastPauseTime==0 && inc>rateOfFire / gs){
        disparo=true;
    }
    
    if(disparo || first_attack){
        detect(e);
        reloj.restart();
    }
}

bool Torreta::inRange(Enemigo* e){
    return (distancev(e->getPosition(),celda->getCenter())<range);
}

Torreta::~Torreta() {
}

