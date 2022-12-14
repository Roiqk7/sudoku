#ifndef DIFFICULTYWINDOW_H
#define DIFFICULTYWINDOW_H

// used in menu and gui when creating new game

#include "constants.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "textBox.h"


class DifficultySelector {
    public:
        bool show;
        static constexpr int margin = 5;

        DifficultySelector() {
            difficultyWindow.setVisible(false);
            show = false;
            init();
        }

        void call(const bool &newGame)
        {
            render(newGame);
        }

    private: 
        sf::RectangleShape frame;
        static constexpr int elementMargin = 5;
        static constexpr int elementWidth = WIDTH_3-3*margin, elementHeight = 40;
        static constexpr int elementSpacing = elementHeight+margin;
        static constexpr int fontSize = 40;

        struct EasyProp
        {
            TextBox box;
            const int xPos = 0+margin, yPos = 0+margin;
            std::string text = " Easy ";
        } easyProp;

        struct MediumProp
        {
            TextBox box;
            const int xPos = 0+margin, yPos = 0+margin+elementSpacing;
            std::string text = "Medium";
        } mediumProp;

        struct hardProp
        {
            TextBox box;
            const int xPos = 0+margin, yPos = 0+margin+2*elementSpacing;
            std::string text = " Hard ";
        } hardProp;

        struct ExpertProp
        {
            TextBox box;
            const int xPos = 0+margin, yPos = 0+margin+3*elementSpacing;
            std::string text = "Expert";
        } expertProp;

        struct RandomProp
        {
            TextBox box;
            const int xPos = 0+margin, yPos = 0+margin+4*elementSpacing;
            std::string text = "Random";
        } randomProp;

        struct ResetProp
        {
            TextBox box;
            const int xPos = 0+margin, yPos = 0+margin+4*elementSpacing;
            std::string text = "Reset";
        } resetProp;

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
            initMenuTextBoxes();
        }

        void initMenuRects()
        {
            frame.setPosition(sf::Vector2f(0, 0));
            frame.setSize(sf::Vector2f(WIDTH, HEIGHT));
            frame.setFillColor(sf::Color{DIFFICULTY_WINDOW_FRAME_COLOR});
        }

        void initMenuTextBoxes()
        {
            initEasyProp();
            initMediumProp();
            initHardProp();
            initExpertProp();
            initRandomProp();
            initResetProp();
        }

        void initEasyProp()
        {
            easyProp.box = TextBox(DIFFICULTY_WIDOW_NUM, elementWidth, elementHeight,
            easyProp.xPos, easyProp.yPos, lawnGreen, easyProp.text, fontSize, 
            black, black, elementMargin);
        }

        void initMediumProp()
        {
            mediumProp.box = TextBox(DIFFICULTY_WIDOW_NUM, elementWidth, elementHeight,
            mediumProp.xPos, mediumProp.yPos, yellow, mediumProp.text, fontSize, 
            black, black, elementMargin);
        }

        void initHardProp()
        {
            hardProp.box = TextBox(DIFFICULTY_WIDOW_NUM, elementWidth, elementHeight,
            hardProp.xPos, hardProp.yPos, orange, hardProp.text, fontSize, 
            black, black, elementMargin);
        }

        void initExpertProp()
        {
            expertProp.box = TextBox(DIFFICULTY_WIDOW_NUM, elementWidth, elementHeight,
            expertProp.xPos, expertProp.yPos, red, expertProp.text, fontSize, 
            black, black, elementMargin);
        }

        void initRandomProp()
        {
            randomProp.box = TextBox(DIFFICULTY_WIDOW_NUM, elementWidth, elementHeight,
            randomProp.xPos, randomProp.yPos, blue, randomProp.text, fontSize, 
            black, black, elementMargin);
        }

        void initResetProp()
        {
            resetProp.box = TextBox(DIFFICULTY_WIDOW_NUM, elementWidth, elementHeight,
            resetProp.xPos, resetProp.yPos, blue, resetProp.text, fontSize, 
            black, black, elementMargin);
            resetProp.box.moveText(13, 0);
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

        void render(const bool &newGame)
        {
            difficultyWindow.draw(frame);
            easyProp.box.call();
            mediumProp.box.call();
            hardProp.box.call();
            expertProp.box.call();
            if (newGame) randomProp.box.call(); 
            else resetProp.box.call();
        }


} difficultySelector;


#endif // DIFFICULTYWINDOW_H