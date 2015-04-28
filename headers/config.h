#ifndef CONFIG_H
#define	CONFIG_H

    #include <algorithm>
    #include <vector>
    #include <string>
    #include <sstream>
    #include <cmath>
    #include <SFML/Graphics.hpp>

    typedef unsigned int uint;
    extern float percent;
    template <typename T> 
    const bool contains( std::vector<T>& Vec, const T& Element ){
        if (std::find(Vec.begin(), Vec.end(), Element) != Vec.end())
            return true;
        return false;
    };

    float random(float,float);
    float distancev(sf::Vector2f v1, sf::Vector2f v2);
    float angle(sf::Vector2f v1, sf::Vector2f v2);
    float mod(float a, float N);
    float toDegrees(float a); 
    std::string convertInt(int number);
#endif	/* CONFIG_H */

