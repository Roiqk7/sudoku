/*
Date: 15/11/2024

This file contains pre-made scenes for the GUI.
*/

#include "../include/colors.hpp"
#include "../include/command.hpp"
#include "../include/guiHelper.hpp"
#include "../include/macros.hpp"
#include "../include/object.hpp"
#include "../include/scene.hpp"
#include "../include/scenes.hpp"
#include <chrono>
#include <filesystem>
#include <functional>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <string>
#include <utility>
#include <vector>

namespace System
{
// Non-game scenes
        /*
        Create the default scene which is active at all times.

        @param scene Scene to create.
        @param window Window to render to.

        @note This scene is used to render error messages etc.
        */
        void createDefaultScene(Scene& scene, const sf::RenderWindow& window)
        {
                LOG_TRACE("createDefaultScene() called.");

                scene.clear();

                scene.name = "Default";

                // Get necessary window information
                sf::Vector2i center = getWindowCenter(getWindowSize(window));
                sf::Vector2u sizeU = getWindowSize(window);
                sf::Vector2i size(sizeU.x, sizeU.y);
                sf::Vector2i topLeft = getWindowTopLeftCorner();

                // Yellow Background
                std::shared_ptr<Object> background = std::make_shared<Rectangle>(
                        "Yellow Background", topLeft.x, topLeft.y,
                        size.x, size.y, Colors::YELLOW);
                scene.addObject(background);

                // Black rectangle
                std::shared_ptr<Object> rect = std::make_shared<Rectangle>(
                        "Black Rectangle", topLeft.x + size.x / 10,
                        topLeft.y + size.y / 10, size.x - size.x / 5,
                        size.y - size.y / 5, Colors::BLACK);
                scene.addObject(rect);

                // Text
                auto font = getFont("font");
                std::shared_ptr<Object> text = std::make_shared<Text>(
                        "Text", center.x/2, center.y, font.first,
                        font.second, "THIS SHOULD BE HIDDEN", center.y / 5,
                        Colors::WHITE);
                scene.addObject(text);
        }

} // namespace System