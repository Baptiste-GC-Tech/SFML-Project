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
		vecResult.x /= vecNorm;
		vecResult.y /= vecNorm;
	}

	return vecResult;
}
float gameObj::angleBetween(sf::Vector2f ARGvecA, sf::Vector2f ARGvecB)
{
	// Calculates the angle. (scalar product / norms product) * (180 / pi) <- tp convert angle in degrees
	float scalarProduct = (ARGvecA.x * ARGvecB.x) + (ARGvecA.y * ARGvecB.y);
	float normProduct = (sqrt(pow(ARGvecA.x, 2) + pow(ARGvecA.y, 2))) * (sqrt(pow(ARGvecB.x, 2) + pow(ARGvecB.y, 2)));
	float angle = acos(scalarProduct / normProduct) * (180 / M_PI);

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
	this->collidingWith = {};

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
	this->collidingWith = {};

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
	// Updates the object position
	this->pos = nextPos;

	// Returns nextPos
	return nextPos;
}
// Spinny spin
void gameObj::rotate(float ARGangleRight)
{
	this->shape->setRotation(this->shape->getRotation() + ARGangleRight);
}

void gameObj::collisionCircleRectangle(sf::Vector2f ARGnextPos, gameObj* ARGobj)
{
	std::cout << "Points colliding : ";

	// This method only works if the calling object as a CircleShape !!!
	bool collided = false;
	sf::Vector2f centerPoint = this->shape->getPosition() + sf::Vector2f(static_cast<sf::CircleShape*>(this->shape)->getRadius(), static_cast<sf::CircleShape*>(this->shape)->getRadius());

	// Test if the right-most point of the circle is inside of the rectangle
	sf::Vector2f rightPoint = this->shape->getPosition() + sf::Vector2f(2 * static_cast<sf::CircleShape*>(this->shape)->getRadius(), 1 * static_cast<sf::CircleShape*>(this->shape)->getRadius());
	if ((rightPoint.x >= ARGobj->shape->getPosition().x && rightPoint.x <= ARGobj->shape->getPosition().x + static_cast<sf::RectangleShape*>(ARGobj->shape)->getSize().x) &&
		(rightPoint.y >= ARGobj->shape->getPosition().y && rightPoint.y <= ARGobj->shape->getPosition().y + static_cast<sf::RectangleShape*>(ARGobj->shape)->getSize().y))
	{
		std::cout << "R ";
		collided = true;
	}
	// Test if the left-most point of the circle is inside of the rectangle
	sf::Vector2f leftPoint = this->shape->getPosition() + sf::Vector2f(0 * static_cast<sf::CircleShape*>(this->shape)->getRadius(), 1 * static_cast<sf::CircleShape*>(this->shape)->getRadius());
	if ((leftPoint.x >= ARGobj->shape->getPosition().x && leftPoint.x <= ARGobj->shape->getPosition().x + static_cast<sf::RectangleShape*>(ARGobj->shape)->getSize().x) &&
		(leftPoint.y >= ARGobj->shape->getPosition().y && leftPoint.y <= ARGobj->shape->getPosition().y + static_cast<sf::RectangleShape*>(ARGobj->shape)->getSize().y))
	{
		std::cout << "L ";
		collided = true;
	}
	// Test if the top-most point of the circle is inside of the rectangle
	sf::Vector2f topPoint = this->shape->getPosition() + sf::Vector2f(1 * static_cast<sf::CircleShape*>(this->shape)->getRadius(), 0 * static_cast<sf::CircleShape*>(this->shape)->getRadius());
	if ((topPoint.x >= ARGobj->shape->getPosition().x && topPoint.x <= ARGobj->shape->getPosition().x + static_cast<sf::RectangleShape*>(ARGobj->shape)->getSize().x) &&
		(topPoint.y >= ARGobj->shape->getPosition().y && topPoint.y <= ARGobj->shape->getPosition().y + static_cast<sf::RectangleShape*>(ARGobj->shape)->getSize().y))
	{
		std::cout << "T ";
		collided = true;
	}
	// Test if the right-most point of the circle is inside of the rectangle
	sf::Vector2f bottomPoint = this->shape->getPosition() + sf::Vector2f(1 * static_cast<sf::CircleShape*>(this->shape)->getRadius(), 2 * static_cast<sf::CircleShape*>(this->shape)->getRadius());
	if ((bottomPoint.x >= ARGobj->shape->getPosition().x && bottomPoint.x <= ARGobj->shape->getPosition().x + static_cast<sf::RectangleShape*>(ARGobj->shape)->getSize().x) &&
		(bottomPoint.y >= ARGobj->shape->getPosition().y && bottomPoint.y <= ARGobj->shape->getPosition().y + static_cast<sf::RectangleShape*>(ARGobj->shape)->getSize().y))
	{
		std::cout << "B ";
		collided = true;
	}
	// Test if the top-right point of the rectangle is inside of the circle
	sf::Vector2f topRight = ARGobj->shape->getPosition() + sf::Vector2f(0 * static_cast<sf::RectangleShape*>(ARGobj->shape)->getSize().x, 0 * static_cast<sf::RectangleShape*>(ARGobj->shape)->getSize().y);
	if (float distance = sqrt(pow(centerPoint.x - topRight.x, 2) + pow(centerPoint.y - topRight.y, 2)) <= static_cast<sf::CircleShape*>(this->shape)->getRadius())
	{
		std::cout << "TR ";
		collided = true;
	}
	// Test if the top-left point of the rectangle is inside of the circle
	sf::Vector2f topLeft = ARGobj->shape->getPosition() + sf::Vector2f(1 * static_cast<sf::RectangleShape*>(ARGobj->shape)->getSize().x, 0 * static_cast<sf::RectangleShape*>(ARGobj->shape)->getSize().y);
	if (float distance = sqrt(pow(centerPoint.x - topLeft.x, 2) + pow(centerPoint.y - topLeft.y, 2)) <= static_cast<sf::CircleShape*>(this->shape)->getRadius())
	{
		std::cout << "TL ";
		collided = true;
	}
	// Test if the bottom-right point of the rectangle is inside of the circle
	sf::Vector2f bottomRight = ARGobj->shape->getPosition() + sf::Vector2f(0 * static_cast<sf::RectangleShape*>(ARGobj->shape)->getSize().x, 1 * static_cast<sf::RectangleShape*>(ARGobj->shape)->getSize().y);
	if (float distance = sqrt(pow(centerPoint.x - bottomRight.x, 2) + pow(centerPoint.y - bottomRight.y, 2)) <= static_cast<sf::CircleShape*>(this->shape)->getRadius())
	{
		std::cout << "BR ";
		collided = true;
	}
	// Test if the bottom-left point of the rectangle is inside of the circle
	sf::Vector2f bottomLeft = ARGobj->shape->getPosition() + sf::Vector2f(1 * static_cast<sf::RectangleShape*>(ARGobj->shape)->getSize().x, 1 * static_cast<sf::RectangleShape*>(ARGobj->shape)->getSize().y);
	if (float distance = sqrt(pow(centerPoint.x - bottomLeft.x, 2) + pow(centerPoint.y - bottomLeft.y, 2)) <= static_cast<sf::CircleShape*>(this->shape)->getRadius())
	{
		std::cout << "BL ";
		collided = true;
	}

	std::cout << "\n";
	// Handles wether or not the obstacle should be in the collidingWith list
	if (collided && std::find(this->collidingWith.begin(), this->collidingWith.end(), ARGobj) == this->collidingWith.end())
		this->collidingWith.push_back(ARGobj);
	else if(!collided)
	{
		auto it = std::find(this->collidingWith.begin(), this->collidingWith.end(), ARGobj);
		if (it != this->collidingWith.end())
			this->collidingWith.erase(it);
	}
}
// Collision checker between the object and the window's borders
void gameObj::windowCollision(sf::RenderWindow& ARGwindow, sf::Vector2f ARGnextPos)
{
	// Stores the object size, regardeless of Shape type, for testing later
	sf::Vector2f objSize;
	if (const sf::CircleShape* circle = dynamic_cast<sf::CircleShape*>(this->shape))
		objSize = sf::Vector2f(2 * circle->getRadius(), 2 * circle->getRadius());
	else if (const sf::RectangleShape* rect = dynamic_cast<sf::RectangleShape*>(this->shape))
		objSize = rect->getSize();

	// Performs the check horizzontally
	if (ARGnextPos.x < 0)
	{
		this->direction.x *= -1;
		this->pos.x = 0;
	}
	if (ARGnextPos.x + objSize.x > ARGwindow.getSize().x)
	{
		this->direction.x *= -1;
		this->pos.x = ARGwindow.getSize().x - objSize.x;
	}

	// Performs the check vertically
	if (ARGnextPos.y < 0)
	{
		this->direction.y *= -1;
		this->pos.y = 0;
	}
	if (ARGnextPos.y + objSize.y > ARGwindow.getSize().y)
	{
		this->direction.y *= -1;
		this->pos.y = ARGwindow.getSize().y - objSize.y;
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
	std::cout << "###ColidingWith: " << this->collidingWith.size() << "\n";
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