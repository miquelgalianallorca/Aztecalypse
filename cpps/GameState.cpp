#include "../headers/GameState.h"

GameState::GameState() {
    paused=false;
    speed=1;
    pause_time=-1;
}

GameState::GameState(const GameState& orig) {
}

void GameState::pause(){
    pause_clock.restart();
    paused=true;
}

void GameState::restart(){
    pause_time=pause_clock.getElapsedTime().asSeconds();
    paused=false;
}

float GameState::getPauseTime(){
    return pause_time;
}

float GameState::getSpeed(){
    return speed;
}

bool GameState::wasPaused(){
    return pause_time!=-1;
}

bool GameState::isPaused(){
    return paused;
}

void GameState::setSpeed(float s){
    speed=s;
}

void GameState::initPauseTime(){
    pause_time=-1;
}

GameState::~GameState() {
}

