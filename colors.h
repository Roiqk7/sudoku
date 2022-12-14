#ifndef COLORS_H
#define COLORS_H

// everything related to colors

#include <array>
#include <iostream>


#define TRANSPARENT 0, 0, 0, 0  
#define SHADOW 255, 255, 255, 150 
#define BLACK 0, 0, 0
#define WHITE 255, 255, 255
#define LIGHT_SKY_BLUE 135, 206, 250
#define NAVAJO_WHITE 255, 222, 173
#define RED 255, 0, 0
#define GREEN 0, 128, 0
#define LAWN_GREEN 124, 252, 0
#define YELLOW 255, 255, 0
#define ORANGE 255, 165, 0
#define BLUE 30, 144, 255

#define MENU_FRAME_COLOR WHITE
#define MENU_BG_COLOR LIGHT_SKY_BLUE
#define DIFFICULTY_WINDOW_FRAME_COLOR WHITE 
#define HUB_COLOR LIGHT_SKY_BLUE
#define BOARD_OUTLINE_COLOR WHITE
#define BOARD_BG_COLOR NAVAJO_WHITE
#define BOARD_TEXT_COLOR WHITE
#define NUMBERS_WINDOW_BG_COLOR WHITE

// highlight
#define MAIN_HIGHLIGHT_COLOR GREEN
#define HIGHLIGHT_COLOR LAWN_GREEN
#define MISTAKE_COLOR RED
#define HINT_HIGHLIGHT_COLOR BLUE

enum Colors {black, white, lightSkyBlue, navajoWhite, 
    red, green, lawnGreen, yellow, orange, blue};

std::array<uint8_t, 3> getColor(const int &color)
{
    std::array<uint8_t, 3> rgb;
    switch (color) {
        case black:
            rgb = {BLACK};
            break;
        case white:
            rgb = {WHITE};
            break;
        case lightSkyBlue:
            rgb = {LIGHT_SKY_BLUE};
            break;
        case navajoWhite:
            rgb = {NAVAJO_WHITE};
            break;
        case red:
            rgb = {RED};
            break;
        case green:
            rgb = {GREEN};
            break;
        case lawnGreen:
            rgb = {LAWN_GREEN};
            break;
        case yellow:
            rgb = {YELLOW};
            break;
        case orange:
            rgb = {ORANGE};
            break;
        case blue:  
            rgb = {BLUE};
            break;
        default:
            rgb = {BLACK};
            break;
    }
    return rgb;
}


#endif // COLORS_H