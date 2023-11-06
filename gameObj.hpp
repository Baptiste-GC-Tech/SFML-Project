#ifndef GAME_OBJ
#define GAME_OBJ

#include <iostream>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>

class gameObj
{
private:
	
	// "Existence" related attributes
	int pos[2];
	sf::Shape* shape;

	// Physics related attributes
	int speed;
	sf::FloatRect boundingBox;
	sf::Vector2f vect;

	// Physics transformations
	void move(sf::Time ARGtime);
	void rotate(sf::Time ARGtime, );
	void bounce();

	// Physics detectors
	bool objCollision();
	bool windowCollision();

public:

	// Constru & Destru
	gameObj(int ARGpos[2], sf::Shape* ARGshape);
	gameObj(int ARGpos[2], sf::Shape* ARGshape, int ARGspeed, sf::Vector2f ARGvect);
	~gameObj();

	// Getters
	int getSpeed();
	int* getPos();
	sf::Shape* getShape();
	sf::Vector2f getVect();
	sf::FloatRect getBoundingBox();

	// Peeker hehehe >:)
	void peek();
};
#endif