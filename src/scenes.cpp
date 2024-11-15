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
        void createDefaultScene(Scene& scene, const sf::RenderWindow& window,
                bool update)
        {
                LOG_TRACE("createDefaultScene() called.");

                scene.clear();

                scene.name = "Default";

                // Text
                auto center = getWindowCenter(getWindowSize(window));
                auto font = getFont("font");
                Text text = Text("Default scene text", center.x, center.y,
                        font.first, font.second, "THIS SHOULD BE HIDDEN", 50,
                        Colors::WHITE);
                std::shared_ptr<Object> pText = std::make_shared<Text>(text);
                scene.addObject(pText);

                // Black Background
                auto sizeU = getWindowSize(window);
                sf::Vector2i size(sizeU.x, sizeU.y);
                sf::Vector2i topLeft = getWindowTopLeftCorner();
                Rectangle background = Rectangle("Background", topLeft.x, topLeft.y,
                        size.x, size.y, Colors::BLACK);
                std::shared_ptr<Object> pBackground = std::make_shared<Rectangle>(background);
                scene.addObject(pBackground);

                // Yellow rectangle
                Rectangle yellow = Rectangle("Background", topLeft.x + 10, topLeft.y + 10,
                        size.x - 20, size.y - 20, Colors::YELLOW);
                std::shared_ptr<Object> pYellow = std::make_shared<Rectangle>(yellow);
                scene.addObject(pYellow);

                if (!update)
                {
                        // Set the update function
                        scene.setUpdateFunction([&window](Scene& s)
                        {
                                createDefaultScene(s, window, true);
                        });
                }
        }

} // namespace System