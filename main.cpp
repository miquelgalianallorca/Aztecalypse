#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <string>
#define kUpdateTimePS 1/15 //15 veces por segundo de la IA
#define kVel 120 //pixeles/segundo
using namespace std;

std::string ItoS(int num){
    std::ostringstream oss;
    oss<<num;
    return oss.str();
}

void updateGameState(int input, float elapsedTimeSinceLastCall, sf::View &view){    
    switch(input){
    case 1:
        view.move(elapsedTimeSinceLastCall*kVel, 0);
        break;
    case 2:
        view.move(-elapsedTimeSinceLastCall*kVel, 0);
        break;
    case 3:
        view.move(0, elapsedTimeSinceLastCall*kVel);
        break;
    case 4:
        view.move(0, -elapsedTimeSinceLastCall*kVel);
        break;
    }
}

int getInput(sf::RenderWindow &window, sf::Event &event, sf::View &view){
    int input = 0;
    //Scroll - Teclas
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) input = 2;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) input = 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) input = 4;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) input = 3;
    //Scroll - Raton
    sf::Vector2i localPosition = sf::Mouse::getPosition(window);
    if(localPosition.x < 25) input = 2;
    if(localPosition.x > (2*view.getSize().x) - 25) input = 1;
    if(localPosition.y < 25) input = 4;
    if(localPosition.y > (2*view.getSize().y) - 25) input = 3;
    //Eventos
    while(window.pollEvent(event)){
        switch(event.type){
            case sf::Event::Closed:
                window.close();
                break;
            break;
        }
    }
    
    return input;
}

int main(int argc, char** argv) {
    sf::RenderWindow window(sf::VideoMode(400, 400), "Entregable - Scrolling", sf::Style::Titlebar | sf::Style::Close);
    //Texturas
    sf::Texture texFondo;
    if(!texFondo.loadFromFile("resources/map.png")){
        std::cerr << "Error cargando la imagen map.png";
        exit(0);
    }
    sf::Sprite fondo(texFondo);
    fondo.setTextureRect(sf::IntRect(0, 0, 832/2, 832/2));
    //View
    sf::View view;
    view.setCenter(sf::Vector2f(350, 300));
    view.setSize(sf::Vector2f(200, 200));
    //Fisicas
    sf::Clock clock;
    
    while(window.isOpen()){
        
        //Update
        if(clock.getElapsedTime().asSeconds() > kUpdateTimePS){
            sf::Event event;
            int input = getInput(window, event, view);
            //std::cout<<ItoS(input);
            updateGameState(input, clock.getElapsedTime().asSeconds(), view);
            clock.restart();
        }
        //Render
        window.clear();
        window.setView(view);
        window.draw(fondo);
        window.display();
    }
    return 0;
}

