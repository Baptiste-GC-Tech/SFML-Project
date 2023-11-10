#include "inputManager.hpp"

/* >========{ Constructors }========< */

// Constructor
inputManager::inputManager(sf::RenderWindow* ARGwindow)
{
	this->window = ARGwindow;
	this->heldInput = {};
}

// Destructor
inputManager::~inputManager()
{
	this->heldInput.clear();

	std::cout << "inputManager was PURGED\n";
}

/* >========{ Constructors }========< */
/* >========{              }========< */
/* >========{    Methods   }========< */

void inputManager::processInput()
{
    // Handles every kind of suppoirted events
    sf::Event event;
    while (this->window->pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;

        case sf::Event::KeyPressed:
            for (const auto it : this->LISTinput)
            {
                if (event.key.code == it.second.key.code)
                    it.first = +1;
            }
            
            break;
        }
    }
}

