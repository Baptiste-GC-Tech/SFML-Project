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
    window.setFramerateLimit(60);

    // Creates a clock to use in the transformation calculations
    sf::Clock clock;

    // #$ DEBUG
    // Test of gameObj class
    gameObj UR(20.f, sf::Vector2f(300.f, 150.f), sf::Vector2f(1.f, 1.f), 100.f);
    gameObj UL(20.f, sf::Vector2f(350.f, 150.f), sf::Vector2f(-2.f, 1.f), 100.f);
    gameObj DL(20.f, sf::Vector2f(400.f, 150.f), sf::Vector2f(-1.f, -1.f), 100.f);
    gameObj DR(20.f, sf::Vector2f(450.f, 150.f), sf::Vector2f(1.f, -1.f), 100.f);

    while (window.isOpen())
    {

        // Starts counting time at begining of loop
        clock.restart();

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
        for (auto obj : UR.getLISTgameObj())
        {
            obj->move(clock.getElapsedTime());
            obj->draw(window);
            obj->showLocalBounds(window);
            obj->showDirectionVector(window);


        }

        // Display what was drawn on the screen, all at once
        window.display();
    }
    return 0;
}