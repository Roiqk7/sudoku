#ifndef CONSTANTS_H
#define CONSTANTS_H

// constant values which need to be global

#include <array>
#include "colors.h"
#include <iostream>
#include <SFML/Graphics.hpp>


// window
#define MAIN_WINDOW_NUM 1       // the window with hub and board 
#define SELECTOR_WINDOW_NUM 2   // secondary smaller window with number input
#define DIFFICULTY_WIDOW_NUM 3  // window for difficulty selection
#define WIDTH 720               // main window, 720 board
#define HEIGHT 790              // main window, 70 hub, 720 board, 5 margin per board side
#define WIDTH_2 84              // selector window, 75 tile size + 9 offset
#define HEIGHT_2 757            // selector window, 10x75 tile size + 7 offset 
#define WIDTH_3 155             // difficulty window, 140 tile size + 3x5 margin
#define HEIGHT_3 235            // difficulty window, 5x40 tile size + 7x5 margin 
#define FPS 60                  // frame rate limit

// return
#define ELEMENT_NOT_FOUND -1
#define NO_NUMBER_SELECTED -1

// board
constexpr int SIZE = 9;
constexpr int EMPTY_NUM = 0;
constexpr char EMPTY_CHAR = '0';
constexpr int INFINITE_VALUE = 99;
enum Diff{easy, medium, hard, expert};

// difficulty window
#define DIFFICULTY_WIN_ELEMENT_COUNT 5

// game over
#define WON 'W'
#define LOST 'L'

// time 
#define COOLDOWN 50000

// windows
sf::RenderWindow window(sf::VideoMode(sf::Vector2u(WIDTH, HEIGHT)), "SUDOKU!");
sf::RenderWindow selectorWindow(sf::VideoMode(sf::Vector2u(WIDTH_2, HEIGHT_2)), "Choose Your Number");
sf::RenderWindow difficultyWindow(sf::VideoMode(sf::Vector2u(WIDTH_3, HEIGHT_3)), "Select difficulty");

// textures
sf::Texture arrowTexture;
#define ARROW_SCALE 0.069
sf::Texture pencilTexture;
#define PENCIL_SCALE 0.08

// include font
sf::Font font;
sf::Font titleFont;
#define PATH_TO_FONT "Desktop/Programming/C:C++/C++/NumeroTres/sudoku/assets/font.ttf"
#define PATH_TO_TITLE_FONT "Desktop/Programming/C:C++/C++/NumeroTres/sudoku/assets/title.ttf"
#define PATH_TO_ARROW_PNG "/Users/roiqk/Desktop/Programming/C:C++/C++/NumeroTres/sudoku/assets/arrow.png"
#define PATH_TO_PENCIL_PNG "/Users/roiqk/Desktop/Programming/C:C++/C++/NumeroTres/sudoku/assets/pencil.png"


#endif // CONSTANTS_H