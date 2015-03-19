#ifndef SFML_H
#define	SFML_H
#include <SFML/Graphics.hpp>
#include <string>

class View {
private: //Atributos
    sf::View* view;
public:  //Metodos
    View(int centerX, int centerY, int sizeX, int sizeY);
    void move(float moveX, float moveY);
    sf::View* getView();
    float getSizeX();
    float getSizeY();
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
    void draw(sf::CircleShape shape);
    void display();
    void setView(View* view);
    sf::RenderWindow* getWindow();
    bool checkEnd();
    bool pollEvent(sf::Event event);
};

class Clock{
private:
    sf::Clock clock;
public:
    Clock();
    float getElapsedTimeAsSeconds();
    float restartAsSeconds();
};

class Mouse{
private:
    int posX;
    int posY;
public:
    Mouse();
    void getPosition(Window* window);
    int getX();
    int getY();
};

class Keyboard{
private:
public:
    Keyboard();
    int getDireccion();
    void getEvent(Window window);
};

#endif	/* SFML_H */

