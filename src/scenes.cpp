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
// System scenes
        /*
        Create the default scene which is active at all times.

        @param scene Scene to create.
        @param window Window to render to.
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
                        "Text", center.x/4 + 10, center.y-80, font.first,
                        font.second, "THIS SHOULD BE HIDDEN", center.y / 5,
                        Colors::WHITE);
                scene.addObject(text);
        }

        /*
        Create the background scene.

        @param scene Scene to create.
        @param window Window to render to.
        */
        void createBackgroundScene(Scene& scene, const sf::RenderWindow& window)
        {
                LOG_TRACE("createBackgroundScene() called.");

                scene.clear();

                scene.name = "Background";

                // Get necessary window information
                sf::Vector2u sizeU = getWindowSize(window);
                sf::Vector2i size(sizeU.x, sizeU.y);
                sf::Vector2i topLeft = getWindowTopLeftCorner();

                // Background
                std::shared_ptr<Object> background = std::make_shared<Rectangle>(
                        "Background", topLeft.x, topLeft.y,
                        size.x, size.y, Colors::LIGHT_SKY_BLUE);
                scene.addObject(background);
        }
// Non-game scenes
        /*
        Create the welcome scene.

        @param scene Scene to create.
        @param window Window to render to.
        */
        void createWelcomeScene(Scene& scene, const sf::RenderWindow& window)
        {
                LOG_TRACE("createWelcomeScene() called."); 

                // TODO: Finish this function and find better way to handle the click-to-continue

                scene.clear();

                scene.name = "Welcome";

                // Get necessary window information
                sf::Vector2i topLeft = getWindowTopLeftCorner();
                sf::Vector2u sizeU = getWindowSize(window);
                sf::Vector2i size(sizeU.x, sizeU.y);
                sf::Vector2i center = getWindowCenter(sizeU);

                // Welcome text
                auto font = getFont("title");
                std::shared_ptr<Object> text = std::make_shared<Text>(
                        "Text", center.x/4 + 10, center.y-80, font.first,
                        font.second, "Welcome!", center.y / 5,
                        Colors::WHITE);
                scene.addObject(text);

                // Click to continue text
                font = getFont("font");
                std::shared_ptr<Object> text2 = std::make_shared<Text>(
                        "Text", center.x/4 + 10, center.y+80, font.first,
                        font.second, "Click anywhere to continue", center.y / 10,
                        Colors::WHITE);
                scene.addObject(text2);

                // Click-to-continue function 
                std::shared_ptr<Command> command = std::make_shared<Command>(
                        [&scene]() { scene.active = false; });

                // Click-to-continue rectangle
                std::shared_ptr<Rectangle> rect = std::make_shared<Rectangle>(
                        "Black Rectangle", topLeft.x, topLeft.y,
                        size.x, size.y, Colors::TRANSPARENT, command);
                scene.addClickableObject(rect); 
        }


} // namespace System