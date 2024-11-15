/*
Date: 15/11/2024

This file contains helper functions for the GUI.
*/

#ifndef GUI_HELPER_HPP
#define GUI_HELPER_HPP

#include <filesystem>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <utility>

namespace System
{
// Window helper functions
        sf::Vector2u getWindowSize(const sf::RenderWindow& window) noexcept;
        sf::Vector2i getWindowCenter(const sf::Vector2u& windowSize) noexcept;
        sf::Vector2i getWindowTopLeftCorner() noexcept;
        sf::Vector2i getWindowTopRightCorner(const sf::Vector2u& windowSize) noexcept;
        sf::Vector2i getWindowBottomLeftCorner(const sf::Vector2u& windowSize) noexcept;
        sf::Vector2i getWindowBottomRightCorner(const sf::Vector2u& windowSize) noexcept;
// Assets helper functions
        std::pair<std::filesystem::path, sf::Font>
                getFont(const std::string& name);
} // namespace System



#endif // !GUI_HELPER_HPP