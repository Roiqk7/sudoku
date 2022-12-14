#ifndef GAMEOVERPROP_H
#define GAMEOVERPROP_H

// renders if game is over
 
#include "constants.h"
#include "gui.h"
#include <iostream>
#include "menu.h"
#include <SFML/Graphics.hpp>
#include <string.h>
#include "text.h"
#include "textBox.h"


class GameOverProp{
    public:
        bool gameOver = false;
        const int width = 450, height = 275;
        const int xPos = WIDTH/2-width/2, yPos = HEIGHT/4;
        const int marginSize = 5;
        sf::RectangleShape shadow;
        sf::RectangleShape frame; 
        sf::RectangleShape background;

        /*
            ####### #       ####### #     # ####### #     # #######  #####  
            #       #       #       ##   ## #       ##    #    #    #     # 
            #       #       #       # # # # #       # #   #    #    #       
            #####   #       #####   #  #  # #####   #  #  #    #     #####  
            #       #       #       #     # #       #   # #    #          # 
            #       #       #       #     # #       #    ##    #    #     # 
            ####### ####### ####### #     # ####### #     #    #     #####  
        */

        BasicText conditionText;
        BasicText timeText;

        class GameOverButtonElement {
            public:   
                TextBox box;

                GameOverButtonElement() {
                    return;
                }

                void init(const int &xPos, const int &yPos, const int &width, const int &height, std::string textContent, 
                    int const &fontSize, const int &marginSize) {
                    box = TextBox(MAIN_WINDOW_NUM, width, height,
                        xPos, yPos, white, textContent, fontSize, 
                        black, black, marginSize);
                }

                void call()
                {
                    render();
                }

            private:  
                void render()
                {
                    box.call();
                }
        };

        const int newGamePropXPos = xPos+marginSize+15, newGamePropYPos = HEIGHT/2;
        const int newGamePropWidth = 255, newGamePropHeigh =  50;
        const int exitPropWidth = 125, exitPropHeigh =  50;
        const int exitPropXPos = xPos+width-marginSize-exitPropWidth-20, exitPropYPos = HEIGHT/2;

        GameOverButtonElement newGameProp;
        GameOverButtonElement exitProp;

        void init(const int &gameOverCondition) {
            gameOver = true;
            this->gameOverCondition = gameOverCondition;
            initiateGameOverProp();
        }

        void call()
        {
            render();
        }

    private:
        int gameOverCondition;

        /*
             ### #     # ### ####### ###    #    ####### ####### 
             #  ##    #  #     #     #    # #      #    #       
             #  # #   #  #     #     #   #   #     #    #       
             #  #  #  #  #     #     #  #     #    #    #####   
             #  #   # #  #     #     #  #######    #    #       
             #  #    ##  #     #     #  #     #    #    #       
            ### #     # ###    #    ### #     #    #    #######                                    
        */

        void initiateGameOverProp()
        {
            initRects();
            initElements();
        }

        void initRects()
        {
            shadow.setPosition(sf::Vector2f(0, 0));
            shadow.setSize(sf::Vector2f(WIDTH, HEIGHT));
            shadow.setFillColor(sf::Color{SHADOW});
            frame.setPosition(sf::Vector2f(xPos, yPos));
            frame.setSize(sf::Vector2f(width, height));
            frame.setFillColor(sf::Color{BLACK});
            background.setPosition(sf::Vector2f(xPos+marginSize, yPos+marginSize));
            background.setSize(sf::Vector2f(width-2*marginSize, height-2*marginSize));
            background.setFillColor(sf::Color{LIGHT_SKY_BLUE});
        }

        void initElements()
        {
            initText();
            initButton();
        }

        void initText()
        {
            // condition text
            int tmpXPos = xPos+marginSize+5, tmpYPos = yPos+marginSize;
            std::string tmpTextContent = getConditionText(gameOverCondition);
            int tmpFontSize = 90;
            conditionText.init(tmpXPos, tmpYPos, tmpTextContent, tmpFontSize);
            // time text
            tmpXPos = xPos+120, tmpYPos = yPos+105;
            tmpTextContent = getFormattedTime();
            tmpFontSize = 65;
            timeText.init(tmpXPos, tmpYPos, tmpTextContent, tmpFontSize);
        }

        void initButton() 
        {
            std::string tmpText = "New game";
            const int fontSize = 55;
            const int marginSize = 5;
            newGameProp.init(newGamePropXPos, newGamePropYPos, newGamePropWidth, newGamePropHeigh, tmpText, fontSize, marginSize);
            tmpText = "Exit";
            exitProp.init(exitPropXPos, exitPropYPos, exitPropWidth, exitPropHeigh, tmpText, fontSize, marginSize);
        }

        std::string getConditionText(const int &gameOverCondition)
        {
            switch (gameOverCondition) {
                case WON:
                    return "YOU WON!";
                case LOST:
                    return "YOU LOST";
                default:   
                    break;
            }
            return "ERROR";
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
            window.draw(shadow);
            window.draw(frame);
            window.draw(background);

            conditionText.call();
            timeText.call();
            newGameProp.call();
            exitProp.call();
        }
};


#endif // GAMEOVERPROP_H