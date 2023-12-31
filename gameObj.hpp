#ifndef GAME_OBJ
#define GAME_OBJ
#define _USE_MATH_DEFINES // Neccessary for pi usage

#include <iostream>
#include <vector>
#include <cmath>

#include <SFML/Graphics.hpp>

class gameObj
{
private:

	/* >========{ Attributes }========< */

	// List of every loaded gameObj
	static std::vector<gameObj*> LISTgameObj;

	// "Existence" related attributes
	sf::Vector2f pos;
	sf::Shape* shape;

	// Physics related attributes
	std::vector<gameObj*> collidingWith;
	sf::Vector2f direction;
	float speed;

	/* >========{     Attributes    }========< */
	/* >========{                   }========< */
	/* >========{    Vector stuff   }========< */

	

public:
	sf::Vector2f normVec(sf::Vector2f ARGvec);
	float angleBetween(sf::Vector2f ARGvecA, sf::Vector2f ARGvecB);

	/* >========{ Constructors }========< */

	// Circle Constructors
	gameObj(float ARGradius, sf::Vector2f ARGpos, sf::Vector2f ARGdirection = sf::Vector2f(1.f, 0.f), float ARGspeed = 0.f);
	
	// Rectangle Constrcutors
	gameObj(sf::Vector2f ARGsize, sf::Vector2f ARGpos, sf::Vector2f ARGdirection = sf::Vector2f(1.f, 0.f), float ARGspeed = 0.f);
	
	// Destructor
	~gameObj();

	/* >========{ Constructors }========< */
	/* >========{              }========< */
	/* >========{    Methods   }========< */

	// Drawing the shape on a window
	void draw(sf::RenderWindow& ARGwin);

	// Physics transformations
	sf::Vector2f move(sf::Time ARGdeltaTime);
	void rotate(float ARGangleRight);

	// Collisions related
	void collisionCircleRectangle(sf::Vector2f nextPosition, gameObj* ARGobj);
	void windowCollision(sf::RenderWindow& ARGwindow, sf::Vector2f ARGnextPos);

	/* >========{ Methods }========< */
	/* >========{         }========< */
	/* >========{ Peekers }========< */

	// Prints an instance's details, or the list of instances
	void peekAtInstance();
	void listAllInstances();

	// Show graphically a couple of useful information about objects on the window
	void showLocalBounds(sf::RenderWindow& ARGwindow);
	void showDirectionVector(sf::RenderWindow& ARGwindow);

	/* >========{   Peekers   }========< */
	/* >========{             }========< */
	/* >========{ Interactors }========< */

	// Getters
	std::vector<gameObj*> getLISTgameObj();
	sf::Shape* getShape();
	sf::Vector2f getPos();
	sf::Vector2f getDirection();
	sf::Vector2f getMousePosition(const sf::RenderWindow& window);
	float getRotation() const;

	// Setters
	void setDirection(sf::Vector2f ARGdirection);
};
#endif