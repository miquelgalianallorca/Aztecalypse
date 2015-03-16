#ifndef SFML_H
#define	SFML_H
#include <SFML/Graphics.hpp>
#include <string>

class View {
private: //Atributos
    sf::View view;
public:  //Metodos
    View(int centerX, int centerY, int sizeX, int sizeY);
    void move(int moveX, int moveY);
    sf::View getView();
};

class Texture{
private:
    sf::Texture texture;
public:
    Texture(char* filename);
    sf::Texture getTexture();
};

class Sprite{
private:
    sf::Sprite sprite;
public:
    Sprite(Texture texture);
    void setTextureRect(int x0, int y0, int xCenter, int yCenter);
    sf::Sprite getSprite();
};

class Window{
private:
    sf::RenderWindow* window;
public:
    Window(int sizeX, int sizeY, std::string nombre);
    bool isOpen();
    void clear();
    void draw(Sprite sprite);
    void display();
    void setView(View view);
    sf::RenderWindow* getWindow();
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
    void getPosition(Window window);
};

class Keyboard{
private:
public:
    Keyboard();
    int getDireccion();
    void getEvent(Window window);
};

#endif	/* SFML_H */

