#ifndef GAME_OBJ
#define GAME_OBJ

#include <iostream>
#include <vector>

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
	sf::Vector2f velocity;

public:

	/* >========{ Constructors }========< */

	// Circle Constructors
	gameObj(sf::Vector2f ARGpos, float ARGradius);
	gameObj(sf::Vector2f ARGpos, float ARGradius, sf::Vector2f ARGvelocity);
	
	// Rectangle Constrcutors
	gameObj(sf::Vector2f ARGpos, sf::Vector2f ARGsize);
	gameObj(sf::Vector2f ARGpos, sf::Vector2f ARGsize, sf::Vector2f ARGvelocity);
	
	// Destructor
	~gameObj();

	/* >========{ Constructors }========< */
	/* >========{              }========< */
	/* >========{    Methods   }========< */

	// Drawing the shape on a window
	void draw(sf::RenderWindow& ARGwin);

	// Physics transformations
	void move(sf::Time ARGdeltaTime);
	void rotate(float ARGangleRight);

	//// Physics detectors
	//bool objCollision();
	//bool windowCollision();

	/* >========{ Methods }========< */
	/* >========{         }========< */
	/* >========{ Peekers }========< */

	// Prints an instance's details, or the list of instances
	void peekAtInstance();
	void listAllInstances();

	/* >========{ Peekers }========< */
	/* >========{         }========< */
	/* >========{ Getters }========< */

	std::vector<gameObj*> getLISTgameObj();
};
#endif