/*
Date: 15/11/2024

This file contains helper functions for the GUI.
*/

#ifndef GUI_HELPER_HPP
#define GUI_HELPER_HPP

#include "colors.hpp"
#include "command.hpp"
#include "gameHandler.hpp"
#include "gui.hpp"
#include "object.hpp"
#include "scene.hpp"
#include <filesystem>
#include <functional>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <string>
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
// Helper structs
        struct WindowInfo
        {
                sf::Vector2u sizeU;
                sf::Vector2i size;
                sf::Vector2i center;
                sf::Vector2i topLeft;
                sf::Vector2i topRight;
                sf::Vector2i bottomLeft;
                sf::Vector2i bottomRight;

                WindowInfo(const sf::Vector2u& sizeU,
                        const sf::Vector2i& size,
                        const sf::Vector2i& center,
                        const sf::Vector2i& topLeft,
                        const sf::Vector2i& topRight,
                        const sf::Vector2i& bottomLeft,
                        const sf::Vector2i& bottomRight);
        };

        struct Button
        {
                std::shared_ptr<Object> frame;
                std::shared_ptr<Rectangle> clickable;
                std::shared_ptr<Object> background;
                std::shared_ptr<Command> command;
                std::shared_ptr<Object> text;

                Button(const std::shared_ptr<Object>& frame,
                        const std::shared_ptr<Rectangle>& clickable,
                        const std::shared_ptr<Object>& background,
                        const std::shared_ptr<Command>& command,
                        const std::shared_ptr<Object>& text);
        };
// Scenes helper
        WindowInfo getWindowInfo(const sf::RenderWindow& window);
        std::shared_ptr<Text> getTitle(const sf::RenderWindow& window);
        Button& createButton(const std::string& name,
                        const int x, const int y,
                        const int width, const int height,
                        const int margin,
                        const sf::Color frameColor,
                        const sf::Color backgroundColor,
                        const std::shared_ptr<Command>& command = nullptr,
                        const std::string& fontName = "", const int fontSize = 0,
                        const std::string& textStr = "",
                        const sf::Color textColor = Colors::WHITE);
        std::shared_ptr<Rectangle> createClickToContinue(
                const std::shared_ptr<Command>& command,
                const sf::RenderWindow& window);
        std::string getFormattedTime(const std::chrono::microseconds& time);
        std::string getFormattedDifficulty(const Sudoku::Difficulty& difficulty);
// Click functions helper
        bool isValidGameSceneMainGridUserInput(
                const int gridValueAtSelectedCell,
                const int selectedCell, const int selectedNumber);
        void gameSceneMainGridUserInputHandle(Scene& scene, GUI& gui,
                const int selectedCell, const int selectedNumber);
        void gameSceneGridInputHandle(Scene& scene, GUI& gui,
                const int selectedCell, const int selectedCellValue,
                const int selectedNumber);
// Click functions
        void gameSceneMainGridClick(Scene& scene, GUI& gui, const int gridSize,
                const int gridX, const int gridY);
        void gameSceneNumberPanelClick(Scene& scene, GUI& gui,
                const int numberPanelSize,
                const int numberPanelX, const int numberPanelY);
} // namespace System



#endif // !GUI_HELPER_HPP