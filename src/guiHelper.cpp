/*
Date: 15/11/2024

This file contains helper functions for the GUI.
*/

#include "../include/guiHelper.hpp"
#include "../include/macros.hpp"
#include <filesystem>
#include <iomanip>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <sstream>
#include <string>
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
// Helper structs
        /*
        Constructor for WindowInfo struct.

        @param sizeU Size of the window.
        @param size Size of the window.
        @param center Center of the window.
        @param topLeft Top left corner of the window.
        @param topRight Top right corner of the window.
        @param bottomLeft Bottom left corner of the window.
        @param bottomRight Bottom right corner of the window.
        */
        WindowInfo::WindowInfo(const sf::Vector2u& sizeU,
                const sf::Vector2i& size,
                const sf::Vector2i& center,
                const sf::Vector2i& topLeft,
                const sf::Vector2i& topRight,
                const sf::Vector2i& bottomLeft,
                const sf::Vector2i& bottomRight)
                : sizeU(sizeU), size(size), center(center),
                topLeft(topLeft), topRight(topRight),
                bottomLeft(bottomLeft), bottomRight(bottomRight)
        {
                LOG_TRACE("WindowInfo::WindowInfo() called.");
        }

        /*
        Constructor for Button struct.

        @param frame Frame of the button.
        @param background Background of the button.
        @param clickable Clickable object of the button.
        @param command Command of the button.
        */
        Button::Button(const std::shared_ptr<Object>& frame,
                const std::shared_ptr<Rectangle>& clickable,
                const std::shared_ptr<Object>& background,
                const std::shared_ptr<Command>& command)
                : frame(frame), clickable(clickable),
                background(background), command(command)
        {
                LOG_TRACE("Button::Button() called.");
        }
// Scenes helper
        /*
        Get the window information.

        @param window Window to get the information from.

        @return The window information.
        */
        WindowInfo getWindowInfo(const sf::RenderWindow& window)
        {
                LOG_TRACE("getWindowInfo() called.");

                return WindowInfo(getWindowSize(window),
                        sf::Vector2i(getWindowSize(window)),
                        getWindowCenter(getWindowSize(window)),
                        getWindowTopLeftCorner(),
                        getWindowTopRightCorner(getWindowSize(window)),
                        getWindowBottomLeftCorner(getWindowSize(window)),
                        getWindowBottomRightCorner(getWindowSize(window)));
        }

        /*
        Get the title object.

        @param window Window to get the center information from.

        @return The title object.
        */
        std::shared_ptr<Text> getTitle(const sf::RenderWindow& window)
        {
                LOG_TRACE("getTitle() called.");

                auto center = getWindowCenter(getWindowSize(window));

                auto titleFont = getFont("title");
                return std::make_shared<Text>(
                        "Title", center.x/2+100, -50, titleFont.first,
                        titleFont.second, "Sudoku", 280,
                        Colors::WHITE);
        }

        /*
        Create a button.

        @param name Name of the button.
        @param x X position of the button.
        @param y Y position of the button.
        @param width Width of the button.
        @param height Height of the button.
        @param margin Margin of the button.
        @param frameColor Color of the frame.
        @param backgroundColor Color of the background.
        @param command Command to execute.

        @return Pointer to the button.

        @note The button is created with a frame, background, and clickable object.
        */
        Button& createButton(const std::string& name,
                        const int x, const int y,
                        const int width, const int height,
                        const int margin,
                        const sf::Color frameColor,
                        const sf::Color backgroundColor,
                        const std::shared_ptr<Command>& command)
        {
                LOG_TRACE("createButton() called.");

                auto frame = std::make_shared<Rectangle>(
                        name + " Frame", x, y, width, height, frameColor);
                auto background = std::make_shared<Rectangle>(
                        name + " Background", x + margin, y + margin,
                        width - 2 * margin, height - 2 * margin, backgroundColor);
                auto clickable = command ? std::make_shared<Rectangle>(
                                name + " Clickable", x, y, width, height,
                                Colors::TRANSPARENT, command)
                        : nullptr;
                return *new Button(frame, clickable, background, command);
        }

        /*
        Create a click anywhere to continue object.

        @param command Command to execute.
        @param window Window to get the size from.

        @return Pointer to the click to continue object.
        */
        std::shared_ptr<Rectangle> createClickToContinue(
                const std::shared_ptr<Command>& command,
                const sf::RenderWindow& window)
        {
                LOG_TRACE("createClickToContinue() called.");

                auto size = getWindowSize(window);
                return std::make_shared<Rectangle>(
                        "Click to continue", 0, 0, size.x, size.y,
                        Colors::TRANSPARENT, command);
        }

        /*
        Get formatted time string.

        @param time Time to format. (format is hh:mm:ss)

        @return Formatted time string.
        */
        std::string getFormattedTime(const std::chrono::microseconds& time)
        {
                LOG_TRACE("getFormattedTime() called.");

                auto hours = std::chrono::duration_cast<std::chrono::hours>(time);
                auto minutes = std::chrono::duration_cast<std::chrono::minutes>(time % hours);
                auto seconds = std::chrono::duration_cast<std::chrono::seconds>(time % minutes);

                std::stringstream ss;
                ss << std::setfill('0') << std::setw(2) << hours.count() << ":"
                        << std::setfill('0') << std::setw(2) << minutes.count() << ":"
                        << std::setfill('0') << std::setw(2) << seconds.count();

                return ss.str();
        }

        /*
        Get formatted game difficulty string.

        @param difficulty Difficulty to format.

        @return Formatted difficulty string.
        */
        std::string getFormattedDifficulty(const Sudoku::Difficulty& difficulty)
        {
                LOG_TRACE("getFormattedDifficulty() called.");

                switch (difficulty)
                {
                        case Sudoku::Difficulty::EASY:
                                return "Easy";
                        case Sudoku::Difficulty::MEDIUM:
                                return "Medium";
                        case Sudoku::Difficulty::HARD:
                                return "Hard";
                        case Sudoku::Difficulty::EXPERT:
                                return "Expert";
                        default:
                                return "None";
                }
        }

} // namespace System