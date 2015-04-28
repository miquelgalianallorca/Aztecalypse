#ifndef GAMESTATE_H
#define	GAMESTATE_H
#include <SFML/Graphics.hpp>
class GameState {
public:
    GameState();
    GameState(const GameState& orig);
    virtual ~GameState();
    
    void pause();
    void restart();
    
    float getPauseTime();
    float getSpeed();
    bool isPaused();
    bool wasPaused();
    
    void setSpeed(float);
    void initPauseTime();

private:
    float speed;
    bool paused;
    
    float pause_time;
    sf::Clock pause_clock;
};
#endif	/* GAMESTATE_H */