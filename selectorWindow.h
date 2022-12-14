#ifndef SELECTORWINDOW_H
#define SELECTORWINDOW_H

// secondary window used to simplify user input

#include <array>
#include <chrono>
#include "constants.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "textBox.h"


int selectedNumber;


class Selector {
    public:
        sf::RectangleShape background;
        sf::RectangleShape arrowBg;
        const int margin = 3;
        const int numSize = WIDTH_2-3*margin;
        struct Element {
            int id;
            TextBox box;
        };
        std::array<Element, SIZE> elements;
        sf::Sprite arrowSprite;

        void init()
        {
            selectorWindow.setVisible(false);
            initBackground();
            initElements();
        }

        void call()
        {
            render();
        }

    private:  
        void initBackground()
        {
            background.setPosition(sf::Vector2f(0, 0));
            background.setSize(sf::Vector2f(WIDTH_2, HEIGHT_2));
            background.setFillColor(sf::Color{NUMBERS_WINDOW_BG_COLOR});
        }

        void initElements()
        {
            // numbers
            for (int i = 0; i < SIZE; i++) {
                elements[i].id = i+1;
                elements[i].box = TextBox(SELECTOR_WINDOW_NUM, numSize, 0+margin, 
                    i*numSize+margin, lightSkyBlue, elements[i].id+EMPTY_CHAR, numSize, 
                    white, white, margin);
                elements[i].box.moveText(15, -5);
            }
            initArrow();
        }

        void initArrow()
        {
            const int xPos = 0+margin, yPos = SIZE*numSize+margin+6;
            arrowBg.setPosition(sf::Vector2f(xPos, yPos));
            arrowBg.setSize(sf::Vector2f(numSize+3, numSize-4));
            arrowBg.setFillColor(sf::Color{LIGHT_SKY_BLUE});
            arrowSprite.setPosition(sf::Vector2f(xPos+4, yPos+13));
            arrowSprite.setScale(sf::Vector2f(ARROW_SCALE, ARROW_SCALE));
            arrowSprite.setTexture(arrowTexture);
        }

        /*
            ######  ####### #     # ######  ####### ######  
            #     # #       ##    # #     # #       #     # 
            #     # #       # #   # #     # #       #     # 
            ######  #####   #  #  # #     # #####   ######  
            #   #   #       #   # # #     # #       #   #   
            #    #  #       #    ## #     # #       #    #  
            #     # ####### #     # ######  ####### #     #                                                
        */

        void render()
        {
            selectorWindow.draw(background);
            for (int i = 0; i < SIZE; i++) {
                elements[i].box.call();
            }
            selectorWindow.draw(arrowBg);
            selectorWindow.draw(arrowSprite);
        }

} selector;


#endif // SELECTORWINDOW_H