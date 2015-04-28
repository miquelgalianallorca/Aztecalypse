#include "../headers/FactoriaEnemigo.h"
#include <SFML/Graphics.hpp>
using namespace std;
FactoriaEnemigo::FactoriaEnemigo() {
}

FactoriaEnemigo::FactoriaEnemigo(const FactoriaEnemigo& orig) {
}
FactoriaEnemigo::FactoriaEnemigo(Celda* lugar,Celda* f, Mapa* m, GameState* gs) {
    /**************************************/
   // std::cout<<"Voy a cargar"<<std::endl;
    //text = ResourceManager::get().getTexture("soldado");
    text=new sf::Texture();
    if (!text->loadFromFile("resources/normal.png"))
    {
        std::cerr << "Error cargando la imagen player.png";
        exit(0);
    }
    //std::cout<<"cargue"<<std::endl;
    gold=0;
    score=0;
    game_state=gs;
    spawn=lugar;
    finish=f;
    spawn->setState(Celda::SPAWN);
    mapa=m;
    path=NULL;
    path=getPath(spawn,finish);
    path->setStates();
}

FactoriaEnemigo::~FactoriaEnemigo() {
}
vector<Enemigo*> FactoriaEnemigo::getEnemigos(){
    return enemigos;
}
bool FactoriaEnemigo::checkPaths(Celda* c,Celda::State s){
    Celda::State ps=c->getState();
    bool exit=true;
    active = false;
    if(s==Celda::OBSTACLE || Celda::TOWER){
        if(ps!=Celda::SPAWN && ps!=Celda::NEXO){
            
            vector<Enemigo*> usu;
            Camino* lp;
            c->setState(s);
            //Cambio el camino principal
            if(path!=NULL && path->hasCell(c)){
                lp=path;
                path=NULL;
                c->setState(s);
                path=getPath(spawn,finish);
                if(path!=NULL){
                    usu=lp->getUsuarios();
                    lp->removeStates();
                    //cout<<"Quito el camino a: "<<usu.size()<<" enemigos."<<endl;
                    for(int a=0,size=usu.size();a<size;a++){
                        usu[a]->setPath(NULL);
                        enemigos_perdidos.push_back(usu[a]);
                    }
                    path->setStates();
                }else{
                    path=lp;
                    c->setState(ps);
                    exit=false;
                }   
            }
            //std::cout<<"Marca 2"<<std::endl;
            vector< Camino* > lps;
            vector< vector< Enemigo*> > usuarios;
            
            if(c->getState()==s){
                for(int a=0,size=caminos.size();a<size;a++){
                    usu=caminos[a]->getUsuarios();
                    caminos[a]->removeStates();

                    usuarios.push_back(usu);
                    lps.push_back(caminos[a]);

                    for(int b=0,size=usu.size();b<size;b++){
                        if(usu[b]!=NULL)
                            usu[b]->setPath(NULL);
                        enemigos_perdidos.push_back(usu[b]);
                    }
                }
                //std::cout<<"Marca 3"<<std::endl;
                c->setState(s);
                
                
                for(int a=0,size=enemigos_perdidos.size();a<size;a++){
                    if(enemigos_perdidos[a]!=NULL && enemigos_perdidos[a]->getCelda()!=NULL){
                        Camino* auxc=getPath(enemigos_perdidos[a]->getCelda(),finish);
                        //std::cout<<"Marca 3.1"<<std::endl;
                        if(auxc!=NULL){
                            enemigos_perdidos[a]->setPath(auxc);
                            auxc->setStates();
                            //std::cout<<"Marca 3.2"<<std::endl;
                            if(auxc!=path && !contains(caminos,auxc))
                                caminos.push_back(auxc);
                        }else{
                            exit=false;
                            //std::cout<<"Marca 3.3"<<std::endl;
                            for(int b=0,size=usuarios.size();b<size;b++){
                                for(int c=0,size=usuarios[b].size();c<size;c++){
                                    usuarios[b][c]->setPath(lps[b]);
                                    lps[b]->setStates();
                                }
                            }
                        }
                    }
                }
                //std::cout<<"Marca 4"<<std::endl;
                if(exit){
                    for (std::vector<Camino*>::iterator it = caminos.begin(); it != caminos.end(); ){
                        if( (*it)->getUsuarios().size()==0 ){
                            (*it)->removeStates();
                            delete * it;  
                            it = caminos.erase(it);
                        }
                        else {
                            ++it;
                        }
                    }
                    for (std::vector<Camino*>::iterator it = caminos.begin(); it != caminos.end(); ++it ){
                        (*it)->setStates();
                    }
                    path->setStates();
                    enemigos_perdidos.clear();
                }
            }
        }else{
            exit=false;
        }
    }else{
        //Otro tipo de cosa
    }
    //std::cout<<"Marca 5"<<std::endl;
    if(exit)
        c->setState(s);
    else
        c->setState(ps);
    
    return exit;
}

Camino* FactoriaEnemigo::getPath(Celda* s, Celda* e){
    
    Camino* nc;
    
    if(path!=NULL){
            nc=path->getSubpath(s,e);
            /*
            std::cout<<"Encuentro subset en el path: "<<std::endl;
            std::cout<<s->getLPos().x<<" , "<<s->getLPos().y<<" - ";
            std::cout<<e->getLPos().x<<" , "<<e->getLPos().y<<std::endl;
            std::cout<<nc->getStart()->getLPos().x<<" , "<<nc->getStart()->getLPos().y<<" - ";
            std::cout<<nc->getEnd()->getLPos().x<<" , "<<nc->getEnd()->getLPos().y<<std::endl;
            */
            if(nc!=NULL){
                return nc;
            }
    }else{
        for(int a=0,size=caminos.size();a<size;a++){
            if(caminos[a]!=NULL){
                nc=caminos[a]->getSubpath(s,e);
                if(nc!=NULL){
                    return nc;
                }
            }
        }
    }
    vector<Celda*> cm=mapa->findPath(s,e);
    
    if(cm.size()>0){
        nc=new Camino(cm);
    }else{
        nc=NULL;
    }
    return nc;
}
void FactoriaEnemigo::update(){
    gold=0;score=0;
    deleteDeads();
    moveEnemies();
    if(!enemigos_espera.empty())
        checkSpawn();
    for(int a=0,size=enemigos.size();a<size;a++){
        enemigos[a]->update();
    }
}
/**************************************************************/
void FactoriaEnemigo::moveEnemies(){
    for(int a=0,size=enemigos.size();a<size;a++){
        if(enemigos[a]->getCelda() == NULL && enemigos[a]->getPath() == NULL)
        {
            cout<<"Teletransporto al enemigo al principio."<<endl;
            enemigos[a]->teleportToPath(path);
        }
            
    }
}
/**************************************************************/

void FactoriaEnemigo::createEnemy(Enemigo::TiposEnemigo e) {
    Enemigo* en;
    if(e==Enemigo::NORMAL){
        en=new EnemigoNormal(game_state,text);
    }else if(e==Enemigo::TANQUE){
        en=new EnemigoTanque(game_state,text);
    }else if(e==Enemigo::RAPIDO){
        en=new EnemigoRapido(game_state,text);
    }
    enemigos.push_back(en);
    en->setPath(path);
    en->setPositionAtCell(path->getStart());
}

void FactoriaEnemigo::createEnemyEspera(Enemigo::TiposEnemigo e){
    enemigos_espera.push_back(e);
}

void FactoriaEnemigo::deleteDeads(){
    Nexo* objetivo=mapa->getNexo(finish);
    float dam=0;
    for (std::vector<Enemigo*>::iterator it = enemigos.begin(); it != enemigos.end(); ){
        if( (*it)->isDead()){
            gold+=(*it)->getGold();
            score+=(*it)->getScore();
            delete * it;  
            it = enemigos.erase(it);
        }else if( (*it)->hasArrived() ){
            if(objetivo!=NULL){
                dam+=(*it)->getDamage();
                //std::cout<<"Le meto "<< (*it)->getDamage() <<" al nexo."<<std::endl;
            }
            delete * it;  
            it = enemigos.erase(it);
        }
        else {
            ++it;
        }
    }
    if(objetivo!=NULL)
        objetivo->quitarVida(dam);
    
    for (std::vector<Camino*>::iterator it = caminos.begin(); it != caminos.end(); ){
        if( (*it)->getUsuarios().size()==0 ){
            (*it)->removeStates();
            delete * it;  
            it = caminos.erase(it);
        }else{
            ++it;
        }
    }
    for (std::vector<Camino*>::iterator it = caminos.begin(); it != caminos.end(); ++it ){
        (*it)->setStates();
    }
    path->setStates();
}

void FactoriaEnemigo::checkSpawn(){
    if(spawnTimer.getElapsedTime().asSeconds()>1.25f){
        createEnemy(enemigos_espera.back());
        enemigos_espera.pop_back();
        spawnTimer.restart();
    }
}