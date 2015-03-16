#include "SFML.h"
#include <SFML/Graphics.hpp>
#include <string>

//**************************************************************** Clase Window
Window::Window(int sizeX, int sizeY, std::string nombre){
   sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(sizeX, sizeY), nombre, sf::Style::Titlebar | sf::Style::Close);
}
sf::RenderWindow* Window::getWindow(){
    return window;
}
bool Window::isOpen(){
    return window->isOpen();
}
void Window::clear(){
    window->clear();
}
void Window::draw(Sprite sprite){
    sf::Sprite s = sprite.getSprite();   
    window->draw(s);
}
void Window::display(){
    window->display();
}
void Window::setView(View view){
    sf::View v = view.getView();
    window->setView(v);
}
//*****************************************************************************

//****************************************************************** Clase View
View::View(int centerX, int centerY, int sizeX, int sizeY) {
    view.setCenter(sf::Vector2f(centerX, centerY));
    view.setSize(sf::Vector2f(sizeX, sizeY)); //Tamano de la window entre 2
}
void View::move(int moveX, int moveY){
    view.move(moveX, moveY);
}
sf::View View::getView(){
    return view;
}
//*****************************************************************************

//*************************************************************** Clase Texture
Texture::Texture(char* filename){
    texture.loadFromFile(filename);
}
sf::Texture Texture::getTexture(){
    return texture;
}
//*****************************************************************************

//*************************************************************** Clase Sprite
Sprite::Sprite(Texture texture){
    sprite = sf::Sprite(texture.getTexture());
}
void Sprite::setTextureRect(int x0, int y0, int xCenter, int yCenter){
    sprite.setTextureRect(sf::IntRect(x0, y0, xCenter, yCenter));
}
sf::Sprite Sprite::getSprite(){
    return sprite;
}
//*****************************************************************************

//*************************************************************** Clase Clock
Clock::Clock(){
    clock = sf::Clock();
}
float Clock::getElapsedTimeAsSeconds(){
    return clock.getElapsedTime().asSeconds();
}
float Clock::restartAsSeconds(){
    return clock.restart().asSeconds();
}
//*****************************************************************************

//*************************************************************** Clase Mouse
Mouse::Mouse(){
    posX = posY = 0;
}
void Mouse::getPosition(Window window){
    sf::Vector2i localPosition = sf::Mouse::getPosition(*window.getWindow());
    posX = localPosition.x;
    posY = localPosition.y;
}
//*****************************************************************************

//************************************************************** Clase Keyboard
Keyboard::Keyboard(){
}
int Keyboard::getDireccion(){
    int input = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) input = 2;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) input = 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) input = 4;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) input = 3;
    return input;
}
void Keyboard::getEvent(Window window){
    sf::Event event;
    sf::RenderWindow* w = window.getWindow();
    while(w->pollEvent(event)){
        switch(event.type){
           case sf::Event::Closed:
                w->close();
                break;
            break;
        }
    }
} 
//*****************************************************************************