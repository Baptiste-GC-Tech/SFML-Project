// Includes for stl
#include <iostream>
#include <array>

// Includes for SFML
#include <SFML/Main.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

// Include for custom classes
#include "gameObj.hpp"

int main()
{
    // Creates the window at half the screen's size
    sf::VideoMode format = sf::VideoMode::getDesktopMode();
    format.height /= 2;
    format.width /= 2;
    sf::RenderWindow window(format, "Physicks");

    // #$ DEBUG
    // Test of gameObj class
    gameObj dummyObj(sf::Vector2f(5.f, 5.f), 30.f);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clears what was previously in the window to re-draw everything again
        window.clear();
        std::cout << "Cleared window\n";

        // Draws everything needed in the window
        dummyObj.draw(window);
        std::cout << "Drawn on window\n";

        // Display what was drawn on the screen, all at once
        window.display();
        std::cout << "Displayed window\n";
    }

    std::cout << "Exiting Normally\n";
    return 0;
}