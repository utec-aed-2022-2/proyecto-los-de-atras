//
// Created by Juan Diego on 11/10/2022.
//

#ifndef BLOCKCHAIN_GUI_H
#define BLOCKCHAIN_GUI_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#if defined _WIN32
    constexpr float cFactor = 0.5f;
#elif defined __linux__
    constexpr float cFactor = 0.6f;
#endif

class Gui {

private:
    sf::RenderWindow* window;

public:

    Gui() = default;
    ~Gui() {
        delete window;
    }

    bool initialize() {
        sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
        window = new sf::RenderWindow(sf::VideoMode((int)(desktop.width * 2.0/3.0), (int)(desktop.height *  2.0/3.0)), "Gui-BlockChain");
        window->setPosition(sf::Vector2<int>((int)(desktop.width/2 - window->getSize().x/2), (int)(desktop.height/2 - window->getSize().y/2)));
        return window->isOpen();
    }

    void runLoop() {
        while (window->isOpen())
        {
            // check all the window's events that were triggered since the last iteration of the loop
            sf::Event event {};
            while (window->pollEvent(event))
            {
                // "close requested" event: we close the window
                if (event.type == sf::Event::Closed)
                    window->close();
            }

            // clear the window with black color
            window->clear(sf::Color::Black);

            // draw everything here...
            // window.draw(...);

            // end the current frame
            window->display();
        }
    }
};


#endif //BLOCKCHAIN_GUI_H
