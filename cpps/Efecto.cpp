/* 
 * File:   Efecto.cpp
 * Author: Alberto
 * 
 * Created on 23 de abril de 2015, 11:17
 */
#include "../headers/Efecto.h"

Efecto::Efecto(const Efecto& orig){
    
}

Efecto::~Efecto() {
}

Efecto::Efecto(Efecto::TYPE t, float v, float d, float a, int i)
{
    type = t;
    value = v;
    area = a;
    duration = d;
    
    id = i;
    times = -1;
    finished = false;
    clock.restart();
    lastPause = 0;
    acc=0;
}

Efecto::Efecto(TYPE t, float v, float n, float d, float a, int i)
{
    type = t;
    value = v;
    area = a;
    duration = d;
    times = n;
    
    id = i;
    finished = false;
    clock.restart();
    lastPause = 0;
    acc=0;
}

Efecto* Efecto::copy(bool copy_area){
    float a = area;
    if(!copy_area)
        a = 0;
    Efecto* e = new Efecto(type, value, times, duration, a, id);
    e->setCancels(getCancels());
    return e;
}

float Efecto::getArea(){
    return area;
}

float Efecto::getValue(){
    return value;
}

float Efecto::getTimes(){
    return times;
}

float Efecto::getDuration(){
    return duration;
}


Efecto::TYPE Efecto::getType(){
    return type;
}

uint Efecto::getId(){
    return id;
}

std::vector<uint> Efecto::getCancels(){
    return ids;
}

bool Efecto::hasFinished(){
    return finished;
}

void Efecto::setCancels(std::vector<uint> v){
    for(uint i=0,sz=v.size();i<sz;i++)
    {
        ids.push_back(v[i]);
    }
}

float Efecto::getRemainingTime(){
    return duration - acc;
}

bool Efecto::apply(float gs)
{
    float dif = clock.restart().asSeconds();
    dif *= gs;
    acc += dif;
    //std::cout<<"Quedan "<<(duration - acc)<<" de slow."<<std::endl;
    bool apply = false;
    if(!finished)
    {
        if(times == -1)//Se aplica solo una vez
        {
            if(duration == 0)//Aplicacion instantanea
            {
                apply = true;
                finished = true;
            }
            else if(duration > acc)//Aplicacion continua
            {
                apply = true;
            }
            if(duration <= acc)
            {
                finished = true;
            }
        }
        else if(times > 0)//Si se aplica varias veces el en tiempo
        {
            if(acc > duration)// Si es hora de
            {                 // aplicarlo
                times-=1;
                apply = true;
                acc = 0;
            }
            finished = (times>0)?false:true;
        }
    }
    else
    {
        std::cout<<"Efecto: He terminado."<<std::endl;
    }
    return apply;
}

void Efecto::restart()
{
    clock.restart();
}