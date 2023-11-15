#include "gameObj.hpp"

std::vector<gameObj*> gameObj::LISTgameObj = {};

/* >========{ Vector Stuff }========< */

sf::Vector2f gameObj::normVec(sf::Vector2f ARGvec)
{
	// Calculates the norm of the direction vector, and prepares the return value
	sf::Vector2f vecResult = ARGvec;
	float vecNorm = sqrt(pow(ARGvec.x, 2) + pow(ARGvec.y, 2));

	// If the norm is neither 1 or -1 EXACTLY, norms the vector
	if (!(vecNorm == 1 || vecNorm == -1))
	{
		// Norms all of the vector's components
		ARGvec.x /= vecNorm;
		ARGvec.y /= vecNorm;
	}

	return vecResult;
}
float gameObj::angleBetween(sf::Vector2f ARGvecA, sf::Vector2f ARGvecB)
{
	// Calculates the angle. (scalar product / norms product) * (180 / pi) <- tp convert angle in degrees
	float scalarProduct = (ARGvecA.x * ARGvecB.x) + (ARGvecA.y * ARGvecB.y);
	float normProduct = (sqrt(pow(ARGvecA.x, 2) + pow(ARGvecA.y, 2))) * (sqrt(pow(ARGvecB.x, 2) + pow(ARGvecB.y, 2)));
	float angle = (scalarProduct / normProduct) * (180 / M_PI);

	return angle;
}


/* >========{ Constructors }========< */

// Circle Constructor
gameObj::gameObj(float ARGradius, sf::Vector2f ARGpos, sf::Vector2f ARGdirection, float ARGspeed)
{
	// Creates a cirlce shape, then sets every value accoding to arguments
	sf::CircleShape* circle = new sf::CircleShape(ARGradius);
	this->shape = circle;
	this->pos = ARGpos;
	this->direction = this->normVec(ARGdirection);
	this->speed = ARGspeed;

	// Adds the gameObj instance to the list
	this->LISTgameObj.push_back(this);
}

// Rectangle Constructor
gameObj::gameObj(sf::Vector2f ARGsize, sf::Vector2f ARGpos, sf::Vector2f ARGdirection, float ARGspeed)
{
	// Creates a rectangle shape, then sets every value accoding to arguments (some by default)
	this->pos = ARGpos;
	sf::RectangleShape* rectangle = new sf::RectangleShape(ARGsize);
	this->shape = rectangle;
	this->direction = this->normVec(ARGdirection);
	this->speed = ARGspeed;

	// Adds the gameObj instance to the list
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

/* >========{ Constructors }========< */
/* >========{              }========< */
/* >========{    Methods   }========< */

// Drawing the shape on a window
void gameObj::draw(sf::RenderWindow& ARGwin)
{
	// Sets it's position, and draws them
	this->shape->setPosition(this->pos);
	ARGwin.draw(*this->shape);
}

// Determines the next position of the gameObj
sf::Vector2f gameObj::move(sf::Time ARGdeltaTime)
{
	// Calculates the position of gameObj after the transformation, assuming no obstacles exist
	sf::Vector2f nextPos = this->getPos();
	nextPos.x += this->direction.x * speed * ARGdeltaTime.asSeconds();
	nextPos.y += this->direction.y * speed * ARGdeltaTime.asSeconds();

	// #$ DEBUG
	// Updates the objetc position
	this->pos = nextPos;

	// Returns nextPos
	return nextPos;
}
// Spinny spin
void gameObj::rotate(float ARGangleRight)
{
	this->shape->setRotation(this->shape->getRotation() + ARGangleRight);
}

// Collision Checker between 2 objects (first one is the one before "." opeartor when  called)
bool gameObj::chkCollision(gameObj* ARGobj)
{
	sf::FloatRect testedBoundBox = this->shape->getLocalBounds();
	sf::FloatRect obstacleBoundBox = ARGobj->shape->getLocalBounds();

	bool result = testedBoundBox.intersects(obstacleBoundBox);
	if (result)
		std::cout << "BOOM\n";
	else
		std::cout << "....\n";

	return result;
}
// Collision checker between the object and the window's borders
void gameObj::winCollision(sf::RenderWindow& ARGwindow, sf::Vector2f ARGnextPos)
{
	// Stores the object siez, regardeless of Shape type, for testing later
	float objSize;
	if (const sf::CircleShape* circle = dynamic_cast<sf::CircleShape*>(this->shape))
		objSize = 2 * circle->getRadius();
	else if (const sf::RectangleShape* rect = dynamic_cast<sf::RectangleShape*>(this->shape))
		objSize = rect->getSize().x;


	// Performs the check horizzontally
	if (ARGnextPos.x < 0 || ARGnextPos.x + objSize > ARGwindow.getSize().x)
	{
		this->direction.x *= -1;
	}

	// Performs the check vertically
	if (ARGnextPos.y < 0 || ARGnextPos.y + objSize > ARGwindow.getSize().y)
	{
		this->direction.y *= -1;
	}
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
		std::cout << "   Circle Shape\nRadius: " << circle->getRadius() << "\n";
	}
	else if (const sf::RectangleShape* rect = dynamic_cast<sf::RectangleShape*>(this->shape))
	{
		std::cout << "   Rectangle Shape\nDimensions: " << rect->getSize().x << ", " << rect->getSize().y << "\n";
	}
	else
	{
		std::cout << "   Unknown Shape\n";
	}
	std::cout << "   Position: " << this->pos.x << ", " << this->pos.y << "\n";
	std::cout << "   Velocity: [" << this->direction.x << ", " << this->direction.y << "] at " << this->speed << "\n";
}
void gameObj::listAllInstances()
{
	std::cout << "gameObj instances :\n";
	for (gameObj* obj : this->LISTgameObj)
	{
		std::cout << "  @: " << obj << "\n";
	}
}

// Show graphically a couple of useful information about objects on the window
void gameObj::showLocalBounds(sf::RenderWindow& ARGwindow)
{
	// Creates a FloatRect to help create a sf::RectangleShape out of it
	sf::FloatRect boundingInfo = this->shape->getLocalBounds();
	sf::RectangleShape boundingBox(sf::Vector2f(boundingInfo.width, boundingInfo.height));

	// Sets up the position and the center of newly created sf::RectangleShape
	boundingBox.setPosition(this->getPos());

	// Sets upwolors and line thickness
	boundingBox.setFillColor(sf::Color::Transparent);
	boundingBox.setOutlineColor(sf::Color::Blue);
	boundingBox.setOutlineThickness(1.5f);

	// Draws the bounding box of the gameObj's Shape
	ARGwindow.draw(boundingBox);
}
void gameObj::showDirectionVector(sf::RenderWindow& ARGwindow)
{
	// Creates a "line", being a 1 by 0 sf::RectangleShape, and sets up its position in the middle of the Shape (supports Circle and Rectangle)
	sf::RectangleShape directionVector(sf::Vector2f(30.f, 1.f));
	if (const sf::CircleShape* circle = dynamic_cast<sf::CircleShape*>(this->shape))
		directionVector.setPosition(this->getPos() + sf::Vector2f(circle->getRadius(), circle->getRadius()));
	if (const sf::RectangleShape* rect = dynamic_cast<sf::RectangleShape*>(this->shape))
		directionVector.setPosition(this->getPos() + sf::Vector2f(rect->getSize().x / 2, rect->getSize().y / 2));

	// Determines the angle (in degrees) that must be passed to setRotation()
	float angle = this->angleBetween(this->direction, sf::Vector2f(1.f, 0.f));
	if (this->direction.y < 0)
		angle *= -1;

	// Finally, sets the "line"'s rotation
	directionVector.setRotation(angle);

	// Sets upwolors and line thickness
	directionVector.setFillColor(sf::Color::Red);

	// Draws the direction vector on the window
	ARGwindow.draw(directionVector);
}

/* >========{ Peekers }========< */
/* >========{         }========< */
/* >========{ Getters }========< */

std::vector<gameObj*> gameObj::getLISTgameObj() { return this->LISTgameObj; }
sf::Shape* gameObj::getShape() { return this->shape; };
sf::Vector2f gameObj::getPos() { return this->pos; }
sf::Vector2f gameObj::getDirection() { return this->direction; }

void gameObj::setDirection(sf::Vector2f ARGdirection) { this->direction = ARGdirection; }