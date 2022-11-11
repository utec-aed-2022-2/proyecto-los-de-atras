//
// Created by Juan Diego on 11/10/2022.
//

#ifndef BLOCKCHAIN_GUI_H
#define BLOCKCHAIN_GUI_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "BlockChain.h"

#if defined _WIN32
    constexpr float cFactor = 0.5f;
#elif defined __linux__
    constexpr float cFactor = 0.6f;
#endif

enum class options {
    addUser,
    loginUser,
    close,
    showTransactions,
};

class Gui {

private:
    sf::RenderWindow* window;
    BlockChain* blockChain;

public:

    Gui() : window(nullptr), blockChain(nullptr) {}
    ~Gui() {
        delete window;
    }

    bool initialize(BlockChain* bch) {
        sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
        window = new sf::RenderWindow(sf::VideoMode((int)(desktop.width * 2.0/3.0), (int)(desktop.height *  2.0/3.0)), "Gui-BlockChain");
        window->setPosition(sf::Vector2<int>((int)(desktop.width/2 - window->getSize().x/2), (int)(desktop.height/2 - window->getSize().y/2)));

        this->blockChain = bch;
        return window->isOpen();
    }

    void loginUser() {

    }

    void closeWindow() {
        this->window->close();
    }

    void showTransactions() {

    }

    void addUser() {

    }

    void runLoop() {
        options option = this->showHome();
        switch (option) {
            case options::loginUser:
                this->loginUser();
                break;
            case options::close:
                this->closeWindow();
                break;
            case options::addUser:
                this->addUser();
                break;
            case options::showTransactions:
                this->showTransactions();
                break;
        }
    }

    options showHome() {
        while (window->isOpen()) {
            // check all the window's events that were triggered since the last iteration of the loop
            sf::Event event {};
            while (window->pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    return options::close;
                }
            }

            window->clear(sf::Color::Black);
            window->display();
        }
        return options::close;
    }
};


#endif //BLOCKCHAIN_GUI_H
