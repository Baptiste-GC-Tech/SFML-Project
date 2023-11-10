#ifndef INPUT_MANAGER
#define INPUT_MANAGER

#include <iostream>
#include <vector>
#include <utility> // std::pair

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

class inputManager
{
private:

	sf::RenderWindow* window;
	std::vector<std::pair<int, sf::Event>> LISTinput; // Stores every input and their duration (in amount of time detected without a Realease)

public:

	/* >========{ Constructors }========< */

	// Constuctor
	inputManager(sf::RenderWindow* ARGwindow);

	// Desrtuctor
	~inputManager();

	/* >========{ Constructors }========< */
	/* >========{              }========< */
	/* >========{    Methods   }========< */

	void processInput();
};

#endif