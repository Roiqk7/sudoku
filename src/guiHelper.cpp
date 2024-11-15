/*
Date: 15/11/2024

This file contains helper functions for the GUI.
*/

#include "../include/guiHelper.hpp"
#include "../include/macros.hpp"
#include <filesystem>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <utility>

namespace System
{
// Window helper functions
        /*
        Get the size of the window.

        @param window Window to get the size of.
        */
        sf::Vector2u getWindowSize(const sf::RenderWindow& window) noexcept
        {
                LOG_TRACE("getWindowSize() called.");

                return window.getSize();
        }

        /*
        Get the center of the window.

        @param windowSize Size of the window.
        */
        sf::Vector2i getWindowCenter(const sf::Vector2u& windowSize) noexcept
        {
                LOG_TRACE("getWindowCenter() called.");

                return sf::Vector2i(windowSize.x / 2, windowSize.y / 2);
        }

        /*
        Get the top left corner of the window.
        */
        sf::Vector2i getWindowTopLeftCorner() noexcept
        {
                LOG_TRACE("getWindowTopLeftCorner() called.");

                return sf::Vector2i(0, 0);
        }

        /*
        Get the top right corner of the window.

        @param windowSize Size of the window.
        */
        sf::Vector2i getWindowTopRightCorner(const sf::Vector2u& windowSize) noexcept
        {
                LOG_TRACE("getWindowTopRightCorner() called.");

                return sf::Vector2i(windowSize.x, 0);
        }

        /*
        Get the bottom left corner of the window.

        @param windowSize Size of the window.
        */
        sf::Vector2i getWindowBottomLeftCorner(const sf::Vector2u& windowSize) noexcept
        {
                LOG_TRACE("getWindowBottomLeftCorner() called.");

                return sf::Vector2i(0, windowSize.y);
        }

        /*
        Get the bottom right corner of the window.

        @param windowSize Size of the window.
        */
        sf::Vector2i getWindowBottomRightCorner(const sf::Vector2u& windowSize) noexcept
        {
                LOG_TRACE("getWindowBottomRightCorner() called.");

                return sf::Vector2i(windowSize.x, windowSize.y);
        }
// Assets helper functions
        /*
        Get the font.

        @param name Name of the font.

        @throw std::runtime_error if the font failed to load.
        */
        std::pair<std::filesystem::path, sf::Font> getFont(const std::string& name)
        {
                LOG_TRACE("getFont() called.");

                sf::Font font;
                std::filesystem::path exePath = std::filesystem::current_path();
                std::filesystem::path fontPath = exePath / "assets/" / (name + ".ttf");

                if (!std::filesystem::exists(fontPath))
                {
                        LOG_CRITICAL("Font file does not exist: {}", fontPath.string());
                        throw std::runtime_error("Font file does not exist: " + fontPath.string());
                }

                if (!font.loadFromFile(fontPath))
                {
                        LOG_CRITICAL("Failed to load font: {} from {}", fontPath.string(), exePath.string());
                        throw std::runtime_error("Failed to load font: " + fontPath.string());
                }

                return std::make_pair(fontPath, font);
        }


} // namespace System