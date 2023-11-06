#include "gameObj.hpp"

// Constru & Destru
gameObj::gameObj(int ARGpos[2], sf::Shape* ARGshape)
{
	this->pos[0] = ARGpos[0];
	this->pos[1] = ARGpos[1];
	this->shape = ARGshape;
	this->speed = 0;
	this->vect = sf::Vector2f(0.f, 0.f);

	this->boundingBox = this->shape->getGlobalBounds();
}
gameObj::gameObj(int ARGpos[2], sf::Shape* ARGshape, int ARGspeed, sf::Vector2f ARGvect)
{
	this->pos[0] = ARGpos[0];
	this->pos[1] = ARGpos[1];
	this->shape = ARGshape;
	this->speed = ARGspeed;
	this->vect = ARGvect;

	this->boundingBox = this->shape->getGlobalBounds();
}
gameObj::~gameObj()
{
	// Destroys and frees class elements of gameObj
	this->shape->~Shape();

	std::cout << "gameObj was PURGED\n";
}

// Getters
int gameObj::getSpeed() { return this->speed; }
int* gameObj::getPos() { return this->pos; }
sf::Shape* gameObj::getShape() { return this->shape; }
sf::Vector2f gameObj::getVect() { return this->vect; }
sf::FloatRect gameObj::getBoundingBox() { return this->boundingBox; }

// Peeker hehehe >:)
void gameObj::peek()
{
	// Placeholder
	// Would print a bunch of useful info in the console
}