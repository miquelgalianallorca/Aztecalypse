#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sstream>
#include <string>
#include "../headers/GameState.h"
#include "../headers/SFML.h"
#include "../headers/Game.h"
#include "../headers/State_Menu.h"
#include "../headers/Nivel.h"
#include "SFML/Audio.hpp"

#define kUpdateTimePS 1/15 //15 veces por segundo de la IA
#define kVel 300 //pixeles/segundo

using namespace std;

/*std::string ItoS(int num){
    std::ostringstream oss;
    oss<<num;
    return oss.str();
}*/

int main(int argc, char** argv) {
    srand (static_cast <unsigned> (time(0)));
    int winSizeX = 1280;
    int winSizeY = 720; 
    GameState* gs = new GameState();
    
    /*
    sf::SoundBuffer pitb;
    if (!pitb.loadFromFile("resources/never.wav")){
       cout << "Failed to load scream sound!" << endl;
        return -1;
    }
    sf::Sound pit;
    pit.setBuffer(pitb);
    pit.play();*/
    
    Window *window = new Window(winSizeX, winSizeY, "Aztecalypse the Game");    
    Game* game = new Game(new State_Menu());    
    
    game->launch(window);
    
    delete window;
    delete game;
    delete gs;
    return 0;
}