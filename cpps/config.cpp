#include "../headers/config.h"
    float percent = 0;
    float distancev(sf::Vector2f v1, sf::Vector2f v2){
        sf::Vector2f dif=v1-v2;
        float res=sqrt(pow(dif.x,2)+pow(dif.y,2));
        return res;
    }
    float angle(sf::Vector2f v1, sf::Vector2f v2){
        //Calcula el angulo que forman la torreta y el enemigo
        sf::Vector2f dif=v1-v2;
        sf::Vector2f orientation(0,-1);
        float angle=atan2(dif.y,dif.x)-atan2(orientation.y,orientation.x);
        return angle;
    }
    float mod(float a, float N){
        float ret = a - N * floor (a / N);
        return ret;
    }
    float random(float LO, float HI)//Random inclusivo
    {
        float r = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
        return r;
    }
    float toDegrees(float a){
        float res;
        res=(360-a*180)/3.14159265359;
        return mod(res,360.0);
    }
    std::string convertInt(int number){
       std::stringstream ss;//create a stringstream
       ss << number;//add number to the stream
       return ss.str();//return a string with the contents of the stream
    }

