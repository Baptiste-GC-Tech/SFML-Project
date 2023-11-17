#include "Canon.hpp"

Canon::Canon(sf::Vector2f ARGSize, sf::Vector2f ARGpos, sf::Color ARGColor)
    : gameObj(ARGSize, ARGpos)
{
    this->canonPos = ARGpos;
    std::cout << "Initial Canon Position: " << this->canonPos.x << ", " << this->canonPos.y << std::endl;
    this->getShape()->setOrigin( 0.f,ARGSize.y / 2.f);
    this->getShape()->setPosition(ARGpos);
    this->getShape()->setFillColor(ARGColor);
}

sf::Vector2f Canon::getPosCannon() {
    return canonPos;
}

sf::Vector2f Canon::getDirectionCannon() {
    return canonDirection;
}

void Canon::updateRotation(float ARGAngle) {
    std::cout << "Updating Rotation to Angle: " << ARGAngle << std::endl;

    this->getShape()->setRotation(ARGAngle);
    this->canonDirection = sf::Vector2f(std::cos(ARGAngle * static_cast<float>(M_PI) / 180),
        std::sin(ARGAngle * static_cast<float>(M_PI) / 180));

    this->canonPos = getPosCannon();  // Utilisez la méthode getPosCannon() du Canon
    std::cout << "Canon Position after Rotation: " << this->canonPos.x << ", " << this->canonPos.y << std::endl;
}