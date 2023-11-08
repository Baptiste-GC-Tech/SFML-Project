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
    sf::RenderWindow window(format, "Phfysicks");

    // #$ DEBUG
    // Absurd framerate limit to avoid flooding the console
    window.setFramerateLimit(1);

    // #$ DEBUG
    // Test of gameObj class
    gameObj dummyCircle(sf::Vector2f(5.f, 5.f), 30.f);
    gameObj dummySquare(sf::Vector2f(100.f, 50.f), sf::Vector2f(30.f, 30.f));

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

        // Draws everything needed in the window
       dummySquare.listAllInstances();
        std::cout << "\n\n Displaying...\n\n";
        for (auto obj : dummyCircle.getLISTgameObj())
        {
            obj->peekAtInstance();
            obj->draw(window);
        }

        // Display what was drawn on the screen, all at once
        window.display();
    }
    return 0;
}