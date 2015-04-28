#ifndef CAMINO_H
#define	CAMINO_H
#include "Celda.h"
class Enemigo;

class Camino {
public:
    Camino();
    Camino(const Camino& orig);
    Camino(std::vector<Celda*>);
    
    Celda* getCell(int);
    Celda* getStart();
    Celda* getEnd();
    int getSize();
    std::vector<Enemigo*> getUsuarios();
    Camino* getSubpath(Celda*,Celda*);
    
    bool hasCell(Celda*);
    
    void addUsuario(Enemigo*);
    void removeUsuario(Enemigo*);
    
    void setStates();
    void removeStates();
    
    virtual ~Camino();
private:
    std::vector<Celda*> camino;
    std::vector<Enemigo*> usuarios;
};

#endif	/* CAMINO_H */