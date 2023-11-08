#include "gameObj.hpp"

std::vector<gameObj*> gameObj::LISTgameObj = {};

/* >========{ Constructors }========< */

// Circle Constructors
gameObj::gameObj(sf::Vector2f ARGpos, float ARGradius)
{
	this->pos = ARGpos;
	sf::CircleShape* circle = new sf::CircleShape(ARGradius);
	this->shape = circle;
	this->velocity = sf::Vector2f(0.f, 0.f);
	this->LISTgameObj.push_back(this);
}
gameObj::gameObj(sf::Vector2f ARGpos, float ARGradius, sf::Vector2f ARGvelocity)
{
	this->pos = ARGpos;
	sf::CircleShape* circle = new sf::CircleShape(ARGradius);
	this->shape = circle;
	this->velocity = ARGvelocity;
	this->LISTgameObj.push_back(this);
}

// Rectangle Constructors
gameObj::gameObj(sf::Vector2f ARGpos, sf::Vector2f ARGsize)
{
	this->pos = ARGpos;
	sf::RectangleShape* rectangle = new sf::RectangleShape(ARGsize);
	this->shape = rectangle;
	this->velocity = sf::Vector2f(0.f, 0.f);
	this->LISTgameObj.push_back(this);
}
gameObj::gameObj(sf::Vector2f ARGpos, sf::Vector2f ARGsize, sf::Vector2f ARGvelocity)
{
	this->pos = ARGpos;
	sf::RectangleShape* rectangle = new sf::RectangleShape(ARGsize);
	this->shape = rectangle;
	this->velocity = ARGvelocity;
	this->LISTgameObj.push_back(this);
}

// Destructor
gameObj::~gameObj()
{
	// Destroys and frees gameObj's Shape attrivutes, and updates its static list
	this->shape->~Shape();
	auto it = std::find(this->LISTgameObj.begin(), this->LISTgameObj.end(), this);
	if (it != this->LISTgameObj.end())
	{
		this->LISTgameObj.erase(it);
	}

	std::cout << "gameObj was PURGED\n";
}

/* >========{ Constrcustors }========< */
/* >========{               }========< */
/* >========{    Methods    }========< */

// Drawing the shape on a window
void gameObj::draw(sf::RenderWindow& ARGwin)
{
	// Sets it's position, and draws them
	this->shape->setPosition(this->pos);
	ARGwin.draw(*this->shape);
}

/* >========{ Methods }========< */
/* >========{         }========< */
/* >========{ Peekers }========< */

// Prints an instance's details, or the list of instances
void gameObj::peekAtInstance()
{
	std::cout << "gameObj instance :\n";
	if (const sf::CircleShape* circle = dynamic_cast<sf::CircleShape*>(this->shape))
	{
		std::cout << "   Circle Shape, radius: " << circle->getRadius() << "\n";
	}
	else if (const sf::RectangleShape* rect = dynamic_cast<sf::RectangleShape*>(this->shape))
	{
		std::cout << "   Rectangle Shape, dimensions: " << rect->getSize().x << ", " << rect->getSize().y << "\n";
	}
	else
	{
		std::cout << "   Unknown Shape\n";
	}
	std::cout << "   Position: " << this->pos.x << ", " << this->pos.y << "\n";
	std::cout << "   Speed: " << this->speed;
	std::cout << "   Orientation: [" << this->movOrientation.x << ", " << this->movOrientation.y << "]\n";
}
void gameObj::listAllInstances()
{
	std::cout << "gameObj instances :\n";
	for (gameObj* obj : this->LISTgameObj)
	{
		std::cout << "  @: " << obj << "\n";
	}
}

/* >========{ Peekers }========< */
/* >========{         }========< */
/* >========{ Getters }========< */

std::vector<gameObj*> gameObj::getLISTgameObj() { return this->LISTgameObj; }