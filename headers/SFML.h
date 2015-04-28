#ifndef SFML_H
#define	SFML_H
#include <SFML/Graphics.hpp>
#include <string>
#include "Mapa.h"

class View {
private: //Atributos
    sf::View* view;
public:  //Metodos
    View(int centerX, int centerY);
    void move(float moveX, float moveY);
    void zoom(float factor);
    sf::View* getView();
    float getSizeX();
    float getSizeY();
    void setSize(float sizeX, float sizeY);
    float getCenterX();
    float getCenterY();
    void setCenter(float x, float y);
    void setViewport(float a, float b, float c, float d);
};

class Texture{
private:
    sf::Texture* texture;
public:
    Texture(std::string filename);
    sf::Texture* getTexture();
};

class Sprite{
private:
    sf::Sprite* sprite;
public:
    Sprite(Texture *texture);
    void setTextureRect(int x0, int y0, int xCenter, int yCenter);
    sf::Sprite* getSprite();
    void setPosition(int x, int y);
    bool getHover(int posX, int posY);
};

class Window{
private:
    sf::RenderWindow* window;
public:
    Window(int sizeX, int sizeY, std::string nombre);
    bool isOpen();
    void close();
    void clear();
    void draw(Sprite* sprite);
    //void draw(sf::CircleShape shape);
    void draw(sf::Drawable* drawable);
    void display();
    void setVSync(bool vs);
    void setView(View* view);
    sf::RenderWindow* getWindow();
    bool checkEnd();
    bool pollEvent(sf::Event event);
    int getSizeX();
    int getSizeY();
};

class Clock{
private:
    sf::Clock clock;
public:
    Clock();
    float getElapsedTimeAsSeconds();
    int getElapsedTimeAsMilliseconds();
    float restartAsSeconds();
    int restartAsMilliseconds();
};

class Mouse{
private:
    int posX;
    int posY;
    int posXview;
    int posYview;
public:
    Mouse();
    void getPosition(Window* window);
    void mapPixelToCoords(int pX, int pY, Window* window, View* view);
    bool isLeftClickPressed();
    bool isRightClickPressed();
    int getX();
    int getY();
    int getPosXview();
    int getPosYview();
};

class Keyboard{
private:
public:
    Keyboard();
    int getDireccion();
    void getEvent(Window window);
    bool getEnemiesGenerated();
};
#endif	/* SFML_H */

