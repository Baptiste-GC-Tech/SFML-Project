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

    // Creates a clock to use in the transformation calculations
    sf::Clock clock;

    // #$ DEBUG
    // Absurd framerate limit to avoid flooding the console
    window.setFramerateLimit(60);

    // #$ DEBUG
    // Test of gameObj class
    gameObj dummySquare(sf::Vector2f(100.f, 50.f), sf::Vector2f(70.f, 120.f), sf::Vector2f(10.f, 10.f));

    while (window.isOpen())
    {

        // Starts counting time at begining of loop
        clock.restart();
        //_sleep(1000 / 60);

        // Closes the window if the cross button was pressed
        // TODO : Move it over to inputManager class when it exists
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clears what was previously in the window to re-draw everything again
        window.clear();

        // Draws everything needed in the window
        for (auto obj : dummySquare.getLISTgameObj())
        {
            obj->move(clock.getElapsedTime());
            obj->draw(window);
        }

        // Display what was drawn on the screen, all at once
        window.display();
    }
    return 0;
}