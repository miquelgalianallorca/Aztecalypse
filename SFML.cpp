#include "SFML.h"
#include <SFML/Graphics.hpp>
#include <string>

//**************************************************************** Clase Window
Window::Window(int sizeX, int sizeY, std::string nombre){
   window = new sf::RenderWindow(sf::VideoMode(sizeX, sizeY), nombre, sf::Style::Titlebar | sf::Style::Close);
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
void Window::draw(Sprite* sprite){
    sf::Sprite* s = sprite->getSprite();   
    window->draw(*s);
}
void Window::draw(sf::CircleShape shape){
    window->draw(shape);
}
void Window::display(){
    window->display();
}
void Window::setView(View* view){
    sf::View* v = view->getView();
    window->setView(*v);
}
bool Window::checkEnd(){
    bool fin;
    sf::Event event;
    while(window->pollEvent(event)){
        if(event.type == sf::Event::Closed){
            window->close();
            fin = true;
        }else{
            fin = false;
        }
    }
    return fin;
}
void Window::close(){
    window->close();
}
bool Window::pollEvent(sf::Event event){
    window->pollEvent(event);
}
//*****************************************************************************

//****************************************************************** Clase View
View::View(int centerX, int centerY, int sizeX, int sizeY) {
    view = new sf::View();
    view->setCenter(sf::Vector2f(centerX, centerY));
    view->setSize(sf::Vector2f(sizeX, sizeY)); //Tamano de la window entre 2
}
void View::move(float moveX, float moveY){
    view->move(moveX, moveY);
}
sf::View* View::getView(){
    return view;
}
float View::getSizeX(){
    return view->getSize().x;
}
float View::getSizeY(){
    return view->getSize().y;
}
//*****************************************************************************

//*************************************************************** Clase Texture
Texture::Texture(std::string filename){
    texture = new sf::Texture();
    texture->loadFromFile(filename);
}
sf::Texture* Texture::getTexture(){
    return texture;
}
//*****************************************************************************

//*************************************************************** Clase Sprite
Sprite::Sprite(Texture *texture){
    sf::Texture* tex = texture->getTexture();
    sprite = new sf::Sprite(*tex);
}
void Sprite::setTextureRect(int x0, int y0, int xCenter, int yCenter){
    sprite->setTextureRect(sf::IntRect(x0, y0, xCenter, yCenter));
}
sf::Sprite* Sprite::getSprite(){
    return sprite;
}
//*****************************************************************************

//*************************************************************** Clase Clock
Clock::Clock(){
    clock = sf::Clock();
    clock.restart();
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
void Mouse::getPosition(Window* window){
    sf::RenderWindow* w = window->getWindow();
    sf::Vector2i localPosition = sf::Mouse::getPosition(*w); //ESTO FALLA
    posX = localPosition.x;
    posY = localPosition.y;
}
int Mouse::getX(){
    return posX;
}
int Mouse::getY(){
    return posY;
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