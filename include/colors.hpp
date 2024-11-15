/*
Date: 15/11/2024

This file contains all the colors used in the GUI.
*/

#ifndef COLORS_HPP
#define COLORS_HPP

#include <SFML/Graphics/Color.hpp>

namespace Colors
{
        const sf::Color TRANSPARENT = sf::Color(0, 0, 0, 0);
        const sf::Color SHADOW = sf::Color(255, 255, 255, 150);
        const sf::Color BLACK = sf::Color(0, 0, 0);
        const sf::Color WHITE = sf::Color(255, 255, 255);
        const sf::Color LIGHT_SKY_BLUE = sf::Color(135, 206, 250);
        const sf::Color NAVAJO_WHITE = sf::Color(255, 222, 173);
        const sf::Color RED = sf::Color(255, 0, 0);
        const sf::Color GREEN = sf::Color(0, 128, 0);
        const sf::Color LAWN_GREEN = sf::Color(124, 252, 0);
        const sf::Color YELLOW = sf::Color(255, 255, 0);
        const sf::Color ORANGE = sf::Color(255, 165, 0);
        const sf::Color BLUE = sf::Color(30, 144, 255);
} // namespace Colors

#endif // COLORS_HPP