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

                scene.name = "Default";

                // Text
                auto center = getWindowCenter(getWindowSize(window));
                auto font = getFont("font");
                std::shared_ptr<Object> text = std::make_shared<Text>(
                        "Default scene text", center.x, center.y,
                        font.first, font.second,
                        "THIS SHOULD BE HIDDEN", Colors::WHITE, 50);
                scene.addObject(text);

                // Background
                auto sizeU = getWindowSize(window);
                sf::Vector2i size(sizeU.x, sizeU.y);
                sf::Vector2i topLeft = getWindowTopLeftCorner();
                sf::RectangleShape backgroundRect(sf::Vector2f(size.x, size.y));
                std::shared_ptr<Object> background = std::make_shared<Rectangle>(
                        "Background", topLeft.x, topLeft.y, size.x, size.y,
                        backgroundRect, Colors::BLACK);
                scene.addObject(background);

                // Set the update function
                scene.setUpdateFunction([&scene, &window](Scene& s) {
                        createDefaultScene(scene, window);
                });
        }

} // namespace System