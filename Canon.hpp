#ifndef CANON_HPP
#define CANON_HPP

#include "gameObj.hpp"  // Assurez-vous d'inclure le fichier de la classe gameObj
#include <SFML/Graphics.hpp>

class Canon : public gameObj
{
private:
    sf::Vector2f canonPos;
    sf::Vector2f canonDirection;

public:
    Canon(sf::Vector2f ARGSize, sf::Vector2f ARGpos, sf::Color ARGColor);

    // Méthodes spécifiques à la classe Canon
    sf::Vector2f getPosCannon();
    sf::Vector2f getDirectionCannon();
    void updateRotation(float ARGAngle);
        
};

#endif