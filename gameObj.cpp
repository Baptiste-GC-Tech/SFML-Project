#include "gameObj.hpp"

// Constru & Destru
gameObj::gameObj(sf::Vector2f ARGpos, float ARGradius)
{
	this->pos = ARGpos;
	sf::CircleShape* circle = new sf::CircleShape(ARGradius);
	this->shape = circle;
	this->speed = 0;


	// this->objList.push_back(this);
}
gameObj::~gameObj()
{
	// Destroys and frees class elements of gameObj
	this->shape->~Shape();

	std::cout << "gameObj was PURGED\n";
}

void gameObj::draw(sf::RenderWindow& ARGwin)
{
	std::cout << "	Entered draw()\n";
	ARGwin.draw(*this->shape);
	std::cout << "	Shape drawn\n";
}