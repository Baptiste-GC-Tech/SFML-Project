#ifndef GAME_OBJ
#define GAME_OBJ

#include <iostream>
#include <array>

#include <SFML/Graphics.hpp>

class gameObj
{
private:
	
	// List of loaded in memory gameObj
	static std::vector<gameObj*> objList;

	// "Existence" related attributes
	sf::Vector2f pos;
	sf::Shape* shape;

	// Physics related attributes
	int speed;

	//// Physics transformations
	//void move(sf::Time ARGtime);
	///*  Rotation of object maybe ?  */
	//void bounce(sf::Shape* ARGcollider, int ARGbounciness);

	//// Physics detectors
	//bool objCollision();
	//bool windowCollision();

public:

	// Constru & Destru
	gameObj(sf::Vector2f ARGpos, float ARGradius);
	gameObj(sf::Vector2f ARGpos, sf::Vector2f ARGsize);
	~gameObj();

	// Drawing the shape on a window
	void draw(sf::RenderWindow& ARGwin);
};
#endif