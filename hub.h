#ifndef HUB_H
#define HUB_H

// upper section of main screen

#include <array>
#include "board.h"
#include "constants.h"
#include "gameboard.h"
#include "gui.h"
#include <iostream>
#include "menu.h"
#include <SFML/Graphics.hpp>
#include <string.h>
#include "textBox.h"


class Hub {
    public:   
        // hub background
        static constexpr int hubXPos = 0, hubYPos = 0;
        static constexpr int hubWidth = WIDTH, hubHeight = 70;
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

        // hub element
        // ? move hubElement variables into struct?
        static constexpr int hubElementYPos = 0+12;
        static constexpr int hubElementMarginSize = 3;
        static constexpr int hubElementHeight = hubHeight-(2*hubElementMarginSize)-22;
        static constexpr int hubElementFontSize = 45;

        class HubElement {
            public:   
                int xPos;
                int width;
                TextBox box;
                std::string text; 

                HubElement() {
                    return;
                }

                void init(const int &xPos, const int &width) {
                    this->xPos = xPos;
                    this->width = width;
                }

                void initText(std::string &text) {
                    this->text = text;
                    box = TextBox(MAIN_WINDOW_NUM, width, hubElementHeight,
                        xPos, hubElementYPos, white, text, hubElementFontSize, 
                        black, black, hubElementMarginSize);
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

        HubElement newGameProp;
        HubElement hintProp;
        HubElement difficultyProp;

        struct PauseButton {
            const int xPos = 2*hubElementMarginSize;
            const int width = 40;
            sf::RectangleShape left;
            sf::RectangleShape right;
            // text box behind
            const int rectXPos = 11, rectYPos = 16;
            const int rectWidth = 12, rectHeight = 37; 
            TextBox box;
            std::string text = " ";
            const int margin = rectWidth+8;
        } pauseButton;

        struct NotesProp {
            const int xPos = WIDTH/2+74;
            const int spriteXPos = xPos+1, spriteYPos = hubElementYPos+3;
            const int width = 40;
            bool active = false;
            sf::Sprite pencilSprite;
            TextBox box;
            std::string text = " ";
        } notesProp;

        struct MistakeCounter {
            const int xPos = WIDTH/2+125;
            const int width = 80;
            TextBox box;
            int mistakes = 0;
            std::string text = "0/3";
        } mistakeCounter;

        struct Timer {
            const int width = 135;
            const int xPos = WIDTH-width-3*hubElementMarginSize-1;
            TextBox box;
            std::string text;
            bool stop = false;
        } timer;
        
        // new game prop
        const int newGameXPos = pauseButton.xPos+pauseButton.width+11;
        const int newGameWidth = 80; 
        std::string newGameText = "New";
        // hint
        const int hintPropXPos = newGameXPos+newGameWidth+11;
        const int hintPropWidth = 104;  
        std::string hintPropText = "Hint";
        // difficulty prop
        const int difficultyPropWidth = 160;
        const int difficultyPropXPos = hintPropXPos+hintPropWidth+11;

        void call()
        {
            render();
        }

        void setMistakeCounter(const int &mistakes)
        {
            mistakeCounter.mistakes = mistakes;
            std::string mistakesText = std::to_string(mistakes)  + "/3";
            mistakeCounter.box.changeText(mistakesText);
        }

        void updateMistakeCounter()
        {
            std::string mistakesText = std::to_string(mistakeCounter.mistakes)  + "/3";
            mistakeCounter.box.changeText(mistakesText);
        }

        void updateTimer()
        {
            std::string text = getFormattedTime();
            timer.box.changeText(text);
        }

        /*
            ### #     # ### ####### ###    #    ####### ####### 
             #  ##    #  #     #     #    # #      #    #       
             #  # #   #  #     #     #   #   #     #    #       
             #  #  #  #  #     #     #  #     #    #    #####   
             #  #   # #  #     #     #  #######    #    #       
             #  #    ##  #     #     #  #     #    #    #       
            ### #     # ###    #    ### #     #    #    #######                                            
        */

        void init()
        {
            background.setFillColor(sf::Color{HUB_COLOR});
            background.setPosition(sf::Vector2f(hubXPos, hubYPos));
            background.setSize(sf::Vector2f(hubWidth, hubHeight));
            initTextBoxes();
            initHubElements();
        }

        void initHubElementText(Board &board) {
            newGameProp.initText(newGameText);
            hintProp.initText(hintPropText);
            std::string difficultyPropText = getDifficulty(board.difficulty);
            difficultyProp.initText(difficultyPropText);
        }

    private:  

        void initHubElements() {
            newGameProp.init(newGameXPos, newGameWidth);
            hintProp.init(hintPropXPos, hintPropWidth);
            difficultyProp.init(difficultyPropXPos, difficultyPropWidth);
        }

        void initTextBoxes()
        {
            initPauseButton();
            initNotesProp();
            initMistakeCounter();
            initTimer();
        }

        void initPauseButton()
        {
            pauseButton.left.setPosition(sf::Vector2f(pauseButton.rectXPos, pauseButton.rectYPos));
            pauseButton.left.setSize(sf::Vector2f(pauseButton.rectWidth, pauseButton.rectHeight));
            pauseButton.left.setFillColor(sf::Color{BLACK});
            pauseButton.right.setPosition(sf::Vector2f(pauseButton.rectXPos+pauseButton.margin, pauseButton.rectYPos));
            pauseButton.right.setSize(sf::Vector2f(pauseButton.rectWidth, pauseButton.rectHeight));
            pauseButton.right.setFillColor(sf::Color{BLACK});
            pauseButton.box = TextBox(MAIN_WINDOW_NUM, pauseButton.width, hubElementHeight,
                pauseButton.xPos, hubElementYPos, white, pauseButton.text, hubElementFontSize, 
                black, black, hubElementMarginSize);
        }

        void initNotesProp()
        {
            notesProp.box = TextBox(MAIN_WINDOW_NUM, notesProp.width, hubElementHeight,
            notesProp.xPos, hubElementYPos, white, notesProp.text, hubElementFontSize, 
            black, black, hubElementMarginSize);
            notesProp.pencilSprite.setPosition(sf::Vector2f(notesProp.spriteXPos, notesProp.spriteYPos));
                notesProp.pencilSprite.setScale(sf::Vector2f(PENCIL_SCALE, PENCIL_SCALE));
                notesProp.pencilSprite.setTexture(pencilTexture);
        }

        void initMistakeCounter()
        {
            mistakeCounter.box = TextBox(MAIN_WINDOW_NUM, mistakeCounter.width, hubElementHeight,
                mistakeCounter.xPos, hubElementYPos, white, mistakeCounter.text, hubElementFontSize, 
                black, black, hubElementMarginSize);
        }

        void initTimer()
        {
            timer.text = getFormattedTime();
            timer.box = TextBox(MAIN_WINDOW_NUM, timer.width, hubElementHeight,
                timer.xPos, hubElementYPos, white, timer.text, hubElementFontSize, 
                black, black, hubElementMarginSize);
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
            window.draw(background);
            pauseButton.box.call();
            window.draw(pauseButton.left);
            window.draw(pauseButton.right);
            notesProp.box.call();
            window.draw(notesProp.pencilSprite);

            newGameProp.call();
            hintProp.call();
            difficultyProp.call();

            mistakeCounter.box.call();
            timer.box.call();
        }

        /*
            #     # ####### #       ######  ####### ######  
            #     # #       #       #     # #       #     # 
            #     # #       #       #     # #       #     # 
            ####### #####   #       ######  #####   ######  
            #     # #       #       #       #       #   #   
            #     # #       #       #       #       #    #  
            #     # ####### ####### #       ####### #     # 
        */

        std::string getDifficulty(const int &difficulty)
        {
            switch (difficulty) {
                case easy:
                    return " Easy ";
                case medium:
                    return "Medium";
                case hard:
                    return " Hard ";
                case expert:
                    return "Expert";
                default:
                    break;
            }
            return "ERROR";
        }
};


#endif // HUB_H