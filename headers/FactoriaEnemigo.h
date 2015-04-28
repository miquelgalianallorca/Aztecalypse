#ifndef FACTORIAENEMIGO_H
#define	FACTORIAENEMIGO_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "Enemigo.h"
#include "Celda.h"
#include "Mapa.h"
#include "ResourceManager.h"

/* CHANGELOG
 * Anyadido el metodo cambiaSpeed que recorre el vector de enemigos y
 *  invoca sus metodos cambiaSpeed. Si alguien quiere cambiar el nombre
 *  que no se corte, porque igual lia un poco 
 * 
 * Falta que al spawnear enemigos, estos se adapten a la velocidad actual
 *  del juego. No lo he hecho porque no sabia si preferiais hacerlo pasandole
 *  otro parametro al constructor de enemigo o de que otra manera.
 */

class FactoriaEnemigo :  public sf::Drawable, public sf::Transformable {
public:
    FactoriaEnemigo();
    FactoriaEnemigo(const FactoriaEnemigo& orig);
    FactoriaEnemigo(Celda* lugar, Celda* f, Mapa* m, GameState* gs);
    float getGold(){return gold;}
    float getScore(){return score;}
    void update();
    Camino* getPath(Celda*,Celda*);
    vector<Enemigo*> getEnemigos();
    bool checkPaths(Celda*,Celda::State);
    void createEnemy(Enemigo::TiposEnemigo);
    void createEnemyEspera(Enemigo::TiposEnemigo);
    void checkSpawn();
    void moveEnemies();
    void setGameSpeed(float*);
    void setPath(vector<Enemigo*> v,Camino* p);
    void addPerdidos(vector<Enemigo*> v);
    void cambiaSpeed(float factor);
    void activaClock();
    void deleteDeads();
    virtual ~FactoriaEnemigo();
    
    sf::Texture * text;
private:
    vector<Enemigo*> enemigos;
    vector<Enemigo::TiposEnemigo> enemigos_espera;
    vector<Enemigo*> enemigos_perdidos;
    sf::Clock spawnTimer;
   
    GameState * game_state;
    
    Mapa* mapa;
    
    Celda* spawn;
    Celda* finish;
    
    float gold,score;
    
    std::vector<Camino*> caminos;
    Camino* path;
    
    bool active;
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        for(int a=0;a<enemigos.size();a++){
            enemigos[a]->render(target,states); 
        }
    }
};
#endif	/* FACTORIAENEMIGO_H */