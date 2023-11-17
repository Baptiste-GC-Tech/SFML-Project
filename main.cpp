// Includes for stl
#include <iostream>
#include <array>
#pragma warning(disable : 4996)
#include <cstdlib>

// Includes for SFML
#include <SFML/Main.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

// Include for custom classes
#include "gameObj.hpp"
#include "Canon.hpp"

int main()
{
    // Creates the window at half the screen's size
    sf::VideoMode format = sf::VideoMode::getDesktopMode();
    format.height /= 2;
    format.width /= 2;
    sf::RenderWindow window(format, "Phfysicks");
    //window.setFramerateLimit(1);

    // Creates a clock to use in the transformation calculations
    sf::Clock clock;

    // #$ DEBUG
    // Test of gameObj class
    Canon canon(sf::Vector2f(100.f, 50.f), sf::Vector2f(500, 200.f), sf::Color(255, 255, 0, 180));
    
    gameObj UR(20.f, sf::Vector2f(250.f, 250.f), sf::Vector2f(1.f, 1.f), 150.f);
    gameObj brick(sf::Vector2f(500.f, 80.f), sf::Vector2f(300.f, 300.f));

    float f = -1.f;

    while (window.isOpen())
    {
        system("cls");
        // Closes the window if the cross button was pressed
        // TODO : Move it over to inputManager class when it exists
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Mouse::Left) {
            gameObj UR(20.f, sf::Vector2f(250.f, 250.f), sf::Vector2f(1.f, 1.f), 150.f);
        }
        // Clears what was previously in the window to re-draw everything again
        window.clear();

        // Draws everything needed in the window
        for (auto obj : UR.getLISTgameObj())
        {
            obj->windowCollision(window, obj->move(clock.getElapsedTime()));

            obj->draw(window);
            obj->showLocalBounds(window);
            obj->showDirectionVector(window);
            if (dynamic_cast<sf::CircleShape*>(obj->getShape()))
            {
                obj->collisionCircleRectangle(obj->move(clock.getElapsedTime()), &brick);
                obj->peekAtInstance();
            }
        }

        canon.updateRotation(canon.angleBetween(canon.getMousePosition(window), (canon.getPosCannon())));
        canon.draw(window);
        //UR.collisionCircleRectangle(UR.move(clock.getElapsedTime()), &brick1);

        // Display what was drawn on the screen, all at once
        window.display();

        // Starts counting time at begining of loop
        clock.restart();
        //_sleep((int)1000 / 250);
    }
    return 0;
}