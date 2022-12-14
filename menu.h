#ifndef MENU_H
#define MENU_H

// gets rendered at the start of the program or during game if resume is clicked

#include "constants.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string.h>
#include "text.h"
#include "textBox.h"
#include "timer.h"


class Menu {
    public:   
        bool show;
        bool newGame;

        Menu() {
            init();
            show = true;
            newGame = true;
        }

        void call()
        {
            render();
        }

        /*
             #####  #       ###  #####  #    # ####### ######  
            #     # #        #  #     # #   #  #       #     # 
            #       #        #  #       #  #   #       #     # 
            #       #        #  #       ###    #####   #     # 
            #       #        #  #       #  #   #       #     # 
            #     # #        #  #     # #   #  #       #     # 
             #####  ####### ###  #####  #    # ####### ######                                         
        */

        bool checkClicked(const int &startPos, const int &size, const int &cursor)
        {
            return (startPos < cursor && cursor < startPos+size);
        }

        void getClickedElement(sf::Vector2i &cursorPos)
        {
            // new game or resume
            if (checkClicked(newGameProp.xPos, newGameProp.width, cursorPos.x) 
                && checkClicked(newGameProp.yPos, elementHeight, cursorPos.y)) {
                    // new game
                    if (newGame) difficultyWindow.setVisible(true);
                    // resume
                    else {
                        show = false;
                        stopTime();
                    }
            }
            // exit 
            if (checkClicked(exitProp.xPos, exitProp.width, cursorPos.x) 
                && checkClicked(exitProp.yPos, elementHeight, cursorPos.y)) 
                    exit(EXIT_SUCCESS);
        }

    private:   
        // menu
        sf::RectangleShape frame;
        sf::RectangleShape background;
        static constexpr int margin = 10;
        // elements
        static constexpr int elementHeight = 45;
        static constexpr int elementMargin = 5;
        static constexpr int elementSpace = elementHeight+2*elementMargin+15;
        static constexpr int fontSize = 50;

        FancyText titleText;
        BasicText waterMark;

        struct NewGameProp {
            const int width = 235; 
            const int xPos = WIDTH/2-width/2-elementMargin, yPos = HEIGHT/2;
            TextBox box;
            std::string text = "New Game";
        } newGameProp;

        struct ResumeProp {
            const int width = 175; 
            const int xPos = WIDTH/2-width/2-elementMargin, yPos = HEIGHT/2;
            TextBox box;
            std::string text = "Resume";
        } resumeProp;

        struct ExitProp {
            const int width = 115; 
            const int xPos = WIDTH/2-width/2-elementMargin, yPos = HEIGHT/2+elementSpace;
            TextBox box;
            std::string text = "Exit";
        } exitProp;

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
            initMenuRects();
            initText();
            initMenuTextBoxes();
        }

        void initMenuRects()
        {
            frame.setPosition(sf::Vector2f(0, 0));
            frame.setSize(sf::Vector2f(WIDTH, HEIGHT));
            frame.setFillColor(sf::Color{MENU_FRAME_COLOR});
            background.setPosition(sf::Vector2f(0+margin, 0+margin));
            background.setSize(sf::Vector2f(WIDTH-2*margin, HEIGHT-2*margin));
            background.setFillColor(sf::Color{MENU_BG_COLOR});
        }

        void initText()
        {
            // title
            int xPos = 80, yPos = 0;
            std::string textContent = "Sudoku";
            int fontSize = 300;
            titleText.init(xPos, yPos, textContent, fontSize);
            // watermark
            xPos = WIDTH-350, yPos = HEIGHT-35;
            textContent = "Created by github.com/Roiqk7";
            fontSize = 20;
            waterMark.init(xPos, yPos, textContent, fontSize);
        }

        void initMenuTextBoxes()
        {
            initNewGameProp();
            initResumeProp();
            initExitProp();
        }

        void initNewGameProp()
        {
            newGameProp.box = TextBox(MAIN_WINDOW_NUM, newGameProp.width, elementHeight,
            newGameProp.xPos, newGameProp.yPos, white, newGameProp.text, fontSize, 
            black, black, elementMargin);
        }

        void initResumeProp()
        {
            resumeProp.box = TextBox(MAIN_WINDOW_NUM, resumeProp.width, elementHeight,
            resumeProp.xPos, resumeProp.yPos, white, resumeProp.text, fontSize, 
            black, black, elementMargin);
        }

        void initExitProp()
        {
            exitProp.box = TextBox(MAIN_WINDOW_NUM, exitProp.width, elementHeight,
            exitProp.xPos, exitProp.yPos, white, exitProp.text, fontSize, 
            black, black, elementMargin);
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
            window.draw(frame);
            window.draw(background);
            titleText.call();
            if (newGame) newGameProp.box.call();
            else resumeProp.box.call();
            exitProp.box.call();
            waterMark.call();
        }
};


#endif // MENU_H