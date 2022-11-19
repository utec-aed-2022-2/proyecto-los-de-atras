//
// Created by Juan Diego on 11/14/2022.
//

#ifndef SFML_BASICS_BUTTON_H
#define SFML_BASICS_BUTTON_H

#include <SFML/Graphics.hpp>
#include "word.h"
#include <iostream>
#include <utility>

struct Button {
private:
    sf::RectangleShape* rectangle;
    Position position;
    Word* word;
    float width;
    float height;

public:
    explicit Button(sf::Color color, float x, float y, float h, float w, const std::string& text, const float& textSize, sf::Color textColor = sf::Color::Yellow, const std::string& path = "./assets/fonts/Raleway-Bold.ttf")
    : width(w), height(h), position(x, y) {
        rectangle = new sf::RectangleShape;
        rectangle->setFillColor(color);
        rectangle->setPosition(x, y);
        rectangle->setSize(sf::Vector2(w, h));
        word = new Word(text, x, y, textSize, textColor, path);

        const sf::FloatRect bounds(word->texto.getLocalBounds());
        const auto box(rectangle->getSize());
        word->texto.setOrigin((bounds.width - box.x) / 2 + bounds.left, (bounds.height - box.y) / 2 + bounds.top);
    }

    void draw(sf::RenderWindow* &window) {
        window->draw(*rectangle);
        window->draw(word->getFont());
    }

    [[nodiscard]] bool isOnBound(int x, int y) const {
        return (static_cast<float>(x) > position.x && static_cast<float>(x) < position.x + width) && (static_cast<float>(y) > position.y && static_cast<float>(y) < position.y + height);
    }

    void updateText(std::string newText) {
        this->word->setText(std::move(newText));
        centerWord();
    }

    void centerWord() {
        const sf::FloatRect bounds(word->texto.getLocalBounds());
        const auto box(rectangle->getSize());
        word->texto.setOrigin((bounds.width - box.x) / 2 + bounds.left, (bounds.height - box.y) / 2 + bounds.top);
    }

    void deleteLastCharacter() {
        if (word->size < 1) {
            return;
        }
        word->mensaje = word->mensaje.substr(0, --word->size);
        word->texto.setString(word->mensaje);
        centerWord();
    }

    void mouseEnterEvent(sf::Color newColor, sf::Color newTextColor = sf::Color::Blue) {
        rectangle->setFillColor(newColor);
        word->texto.setFillColor(newTextColor);
    }

    void mouseLeaveEvent(sf::Color newColor, sf::Color newTextColor = sf::Color::Yellow) {
        rectangle->setFillColor(newColor);
        word->texto.setFillColor(newTextColor);
    }

    Word* &getWord() {
        return this->word;
    }
};


#endif //SFML_BASICS_BUTTON_H
