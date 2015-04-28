#include "../headers/SFML.h"
#include <SFML/Graphics.hpp>
#include <string>

//**************************************************************** Clase Window
Window::Window(int sizeX, int sizeY, std::string nombre){
   window = new sf::RenderWindow(sf::VideoMode(sizeX, sizeY), nombre, sf::Style::Titlebar | sf::Style::Close);
   window->setFramerateLimit(60);
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
void Window::draw(sf::Drawable* drawable){
    window->draw(*drawable);
}
/*void Window::draw(sf::CircleShape shape){
    window->draw(shape);
}*/
void Window::display(){
    window->display();
}
void Window::setView(View* view){
    sf::View* v = view->getView();
    window->setView(*v);
}
void Window::setVSync(bool vs){
    window->setVerticalSyncEnabled(vs);
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
int Window::getSizeX(){
    return window->getSize().x;
}
int Window::getSizeY(){
    return window->getSize().y;
}
//*****************************************************************************

//****************************************************************** Clase View
View::View(int centerX, int centerY) {
    view = new sf::View();
    view->setCenter(sf::Vector2f(centerX, centerY));
}
void View::move(float moveX, float moveY){
    view->move(moveX, moveY);
}
void View::zoom(float factor){
    view->zoom(factor);
}
void View::setSize(float sizeX, float sizeY){
    view->setSize(sizeX, sizeY);
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
float View::getCenterX(){
    return view->getCenter().x;
}
float View::getCenterY(){
    return view->getCenter().y;
}
void View::setCenter(float x, float y){
    view->setCenter(x, y);
}
void View::setViewport(float a, float b, float c, float d){
    view->setViewport(sf::FloatRect(a, b, c, d));
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
void Sprite::setPosition(int x, int y){
    sprite->setPosition(x, y);
}
bool Sprite::getHover(int posX, int posY){
    return sprite->getGlobalBounds().contains(posX, posY);
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
int Clock::getElapsedTimeAsMilliseconds(){
    return clock.getElapsedTime().asMilliseconds();
}
float Clock::restartAsSeconds(){
    return clock.restart().asSeconds();
}
int Clock::restartAsMilliseconds(){
    return clock.restart().asMilliseconds();
}
//*****************************************************************************

//*************************************************************** Clase Mouse
Mouse::Mouse(){
    posX = posY = posXview = posYview = 0;
}
void Mouse::getPosition(Window* window){
    sf::RenderWindow* w = window->getWindow();
    sf::Vector2i localPosition = sf::Mouse::getPosition(*w);
    posX = localPosition.x;
    posY = localPosition.y;
}
void Mouse::mapPixelToCoords(int pX, int pY, Window* window, View* view){
    sf::RenderWindow* w = window->getWindow();
    sf::View* v = view->getView();
    sf::Vector2f mapCoords = w->mapPixelToCoords(sf::Vector2i(pX, pY), *v);
    posXview = mapCoords.x;
    posYview = mapCoords.y;
}
bool Mouse::isLeftClickPressed(){
    return sf::Mouse::isButtonPressed(sf::Mouse::Left);
}
bool Mouse::isRightClickPressed(){
    return sf::Mouse::isButtonPressed(sf::Mouse::Right);
}
int Mouse::getX(){
    return posX;
}
int Mouse::getY(){
    return posY;
}
int Mouse::getPosXview(){
    return posXview;
}
int Mouse::getPosYview(){
    return posYview;
}
//*****************************************************************************

//************************************************************** Clase Keyboard
Keyboard::Keyboard(){
}
int Keyboard::getDireccion(){
    int input = 0;
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            ||(sf::Keyboard::isKeyPressed(sf::Keyboard::A))) input = 2;
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            ||(sf::Keyboard::isKeyPressed(sf::Keyboard::D))) input = 1;
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            ||(sf::Keyboard::isKeyPressed(sf::Keyboard::W))) input = 4;
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            ||(sf::Keyboard::isKeyPressed(sf::Keyboard::S))) input = 3;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add)) input = 5;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract)) input = 6;
    return input;
}
bool Keyboard::getEnemiesGenerated(){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)) return true;
    else return false;
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