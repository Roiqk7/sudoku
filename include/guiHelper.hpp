/*
Date: 15/11/2024

This file contains helper functions for the GUI.
*/

#ifndef GUI_HELPER_HPP
#define GUI_HELPER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

namespace System
{
// Window helper functions
        sf::Vector2u getWindowSize(const sf::RenderWindow& window) noexcept;
        sf::Vector2u getWindowCenter(const sf::Vector2u& windowSize) noexcept;
        sf::Vector2u getWindowTopLeftCorner() noexcept;
        sf::Vector2u getWindowTopRightCorner(const sf::Vector2u& windowSize) noexcept;
        sf::Vector2u getWindowBottomLeftCorner(const sf::Vector2u& windowSize) noexcept;
        sf::Vector2u getWindowBottomRightCorner(const sf::Vector2u& windowSize) noexcept;
} // namespace System



#endif // !GUI_HELPER_HPP