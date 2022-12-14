#ifndef TEXT_H
#define TEXT_H

// renders raw text

#include "constants.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string.h>
#include "textBox.h"

class BasicText {
    public:   
        sf::Text text;

        BasicText() {
            return;
        }

        void init(const int &xPos, const int &yPos, std::string textContent, int const &fontSize) {
            text.setFont(font);
            text.setPosition(sf::Vector2f(xPos, yPos));
            text.setString(textContent);
            text.setCharacterSize(fontSize);
        }

        void call()
        {
            render();
        }

    private:  
        void render()
        {
            window.draw(text);
        }
};

class FancyText {
    public:   
        sf::Text text;

        FancyText() {
            return;
        }

        void init(const int &xPos, const int &yPos, std::string textContent, int const &fontSize) {
            text.setFont(titleFont);
            text.setPosition(sf::Vector2f(xPos, yPos));
            text.setString(textContent);
            text.setCharacterSize(fontSize);
        }

        void call()
        {
            render();
        }

    private:  
        void render()
        {
            window.draw(text);
        }
};

#endif // TEXT_H