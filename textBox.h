#ifndef TEXTBOX_H
#define TEXTBOX_H

// used for all graphics which involves text and also draws itself when called using call()

#include <array>
#include "constants.h"
#include <iostream>
#include <string.h>
#include <SFML/Graphics.hpp>

// ! support for dark mode -> make enum so that if you color-- it switches to dark mode alternative and vice versa

class TextBox {
    public: 
        // general highlight
        bool highlight;
        // highlight of tile user clicked on and same number as user clicked on
        bool mainHighlight;
        // if is mistake then overwrite main highlight color 
        bool mistakeHighlight;
        // if user wanted a hint
        bool hintHighlight;

        /*
             #####  ####### #     #  #####  ####### ######  #     #  #####  ####### ####### ######   #####  
            #     # #     # ##    # #     #    #    #     # #     # #     #    #    #     # #     # #     # 
            #       #     # # #   # #          #    #     # #     # #          #    #     # #     # #       
            #       #     # #  #  #  #####     #    ######  #     # #          #    #     # ######   #####  
            #       #     # #   # #       #    #    #   #   #     # #          #    #     # #   #         # 
            #     # #     # #    ## #     #    #    #    #  #     # #     #    #    #     # #    #  #     # 
             #####  ####### #     #  #####     #    #     #  #####   #####     #    ####### #     #  #####  
            Several constructors for different purposes.                                                                               
        */

        TextBox(){
            textContent = "ADD TEXT";
            margin = false;
            highlight = false;
            mainHighlight = false;
            mistakeHighlight = false;
            hintHighlight = false;
        };   

        // board number specific
        TextBox(const int selectedWindow, const int &size, 
                const int &xPos, const int &yPos, const int color,
                const char &num, const int &fontSize, const int fontColor,
                const int marginColor, const int &marginSize) {
            this->selectedWindow = selectedWindow;
            width = height = size+marginSize;
            this->xPos = xPos;
            this->yPos = yPos;
            this->color = color;
            if (num == EMPTY_CHAR) textContent = ' ';
            else this->textContent = num;
            this->fontSize = fontSize;
            this->fontColor = fontColor;
            margin = true;
            this->marginColor = marginColor;
            this->marginSize = marginSize;
            highlight = false;
            mainHighlight = false;
            mistakeHighlight = false;
            hintHighlight = false;
            createRects();
            addText();
        } 

        // general purpose - no margin
        TextBox(const int selectedWindow, const int &width, const int &height, 
                const int &xPos, const int &yPos, int color,
                std::string &textContent, const int &fontSize, const int fontColor) {
            this->selectedWindow = selectedWindow;
            this->width = width;
            this->height = height;
            this->xPos = xPos;
            this->yPos = yPos;
            this->color = color;
            this->textContent = textContent;
            this->fontSize = fontSize;
            this->fontColor = fontColor;
            highlight = false;
            mainHighlight = false;
            mistakeHighlight = false;
            hintHighlight = false;
            createRects();
            addText();
        } 

        // general purpose - margin included
        TextBox(const int selectedWindow, const int &width, const int &height, 
                const int &xPos, const int &yPos, const int color,
                std::string &textContent, const int &fontSize, const int fontColor, 
                const int marginColor, const int &marginSize) {
            this->selectedWindow = selectedWindow;
            this->width = width+marginSize;
            this->height = height+marginSize;
            this->xPos = xPos;
            this->yPos = yPos;
            this->color = color;
            this->textContent = textContent;
            this->fontSize = fontSize;
            this->fontColor = fontColor;
            margin = true;
            this->marginColor = marginColor;
            this->marginSize = marginSize;
            highlight = false;
            mainHighlight = false;
            mistakeHighlight = false;
            hintHighlight = false;
            createRects();
            addText();
        }

        /*
            ####### #     # #     #  #####  ####### ### ####### #     #  #####  
            #       #     # ##    # #     #    #     #  #     # ##    # #     # 
            #       #     # # #   # #          #     #  #     # # #   # #       
            #####   #     # #  #  # #          #     #  #     # #  #  #  #####  
            #       #     # #   # # #          #     #  #     # #   # #       # 
            #       #     # #    ## #     #    #     #  #     # #    ## #     # 
            #        #####  #     #  #####     #    ### ####### #     #  #####  
        */

        void changeColor(const int &color)
        {
            this->color = color;
            paint();
        }

        void changeText(std::string textContent)
        {
            this->textContent = textContent; 
            text.setString(textContent);    
        }

        void changeText(const int &number)
        {
            if (number == EMPTY_NUM) this->textContent = ' ';
            else this->textContent = number+EMPTY_CHAR; 
            text.setString(textContent);    
        }

        void moveText(const int &xChange, const int &yChange)
        {
            text.setPosition(sf::Vector2f(xPos+xChange, yPos-5+yChange));
        }

        void call()
        {
            render();
        }

    private:  
        sf::RectangleShape frame;
        sf::RectangleShape  background;
        // determine on which window to show the text box
        int selectedWindow;
        // if box will be button -> action determined by text
        int width, height;
        // top left corner (including margin if present)
        int xPos, yPos;
        // text related
        std::string textContent;
        sf::Text text;
        int fontSize;
        int fontColor;
        // id of color
        int color;
        // holds rgb values
        std::array<uint8_t, 3> rgbBg;
        std::array<uint8_t, 3> rgbFrame;
        std::array<uint8_t, 3> rgbFont;
        // space around the main box
        bool margin;
        int marginColor;
        int marginSize;

        /*
             #####  #######  #####  #     # ####### ####### ###  #####   #####  
            #     # #     # #     # ##   ## #          #     #  #     # #     # 
            #       #     # #       # # # # #          #     #  #       #       
            #       #     #  #####  #  #  # #####      #     #  #        #####  
            #       #     #       # #     # #          #     #  #             # 
            #     # #     # #     # #     # #          #     #  #     # #     # 
             #####  #######  #####  #     # #######    #    ###  #####   #####      
            What user sees on the screen.                                                       
        */

        void render()
        {
            if (mistakeHighlight)  background.setFillColor(sf::Color{MISTAKE_COLOR});
            else {
                if (hintHighlight) background.setFillColor(sf::Color{HINT_HIGHLIGHT_COLOR});
                else if (mainHighlight)  background.setFillColor(sf::Color{MAIN_HIGHLIGHT_COLOR});
                else if (highlight)  background.setFillColor(sf::Color{HIGHLIGHT_COLOR});
                else  background.setFillColor(sf::Color{rgbBg[0], rgbBg[1], rgbBg[2]});
            }
            if (selectedWindow == MAIN_WINDOW_NUM) {
                if (margin) window.draw(frame);
                window.draw( background);
                window.draw(text);
            }
            else if (selectedWindow == SELECTOR_WINDOW_NUM) {
                if (margin) selectorWindow.draw(frame);
                selectorWindow.draw( background);
                selectorWindow.draw(text);
            }
            else if (selectedWindow == DIFFICULTY_WIDOW_NUM) {
                if (margin) difficultyWindow.draw(frame);
                difficultyWindow.draw( background);
                difficultyWindow.draw(text);
            }
        }

        void createRects()
        {
            createBg();
            if (margin) createFrame();
            paint();
        }

        void createBg()
        {
             background.setPosition(sf::Vector2f(xPos, yPos));
             background.setSize(sf::Vector2f(width, height));
        }

        void createFrame()
        {
            frame.setPosition(sf::Vector2f(xPos-marginSize, yPos-marginSize));
            frame.setSize(sf::Vector2f(width+2*marginSize, height+2*marginSize));
        }

        void addText()
        {
            text.setPosition(sf::Vector2f(xPos, yPos-5));
            text.setFont(font);
            text.setCharacterSize(fontSize);
            text.setString(textContent);
        }

        void paint()
        {
            rgbBg = getColor(color);
             background.setFillColor(sf::Color{rgbBg[0], rgbBg[1], rgbBg[2]});
            rgbFont = getColor(fontColor);
            text.setFillColor(sf::Color{rgbFont[0], rgbFont[1], rgbFont[2]});
            if (margin) {
                rgbFrame = getColor(marginColor);
                frame.setFillColor(sf::Color{rgbFrame[0], rgbFrame[1], rgbFrame[2]});
            }
        }   
};


#endif // TEXTBOX_H