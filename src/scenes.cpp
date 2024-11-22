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
        void createDefaultScene(Scene& scene, sf::RenderWindow& window)
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
        void createBackgroundScene(Scene& scene, sf::RenderWindow& window)
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
        void createWelcomeScene(Scene& scene, sf::RenderWindow& window)
        {
                LOG_TRACE("createWelcomeScene() called."); 

                scene.clear();

                scene.name = "Welcome";

                // Get necessary window information
                sf::Vector2i topLeft = getWindowTopLeftCorner();
                sf::Vector2u sizeU = getWindowSize(window);
                sf::Vector2i size(sizeU.x, sizeU.y);
                sf::Vector2i center = getWindowCenter(sizeU);

                // Sudoku title
                auto titleFont = getFont("title");
                std::shared_ptr<Object> title = std::make_shared<Text>(
                        "Text", center.x/2+100, -50, titleFont.first,
                        titleFont.second, "Sudoku", 280,
                        Colors::WHITE);
                scene.addObject(title);

                // Welcome text
                auto font = getFont("font");
                std::shared_ptr<Object> text = std::make_shared<Text>(
                        "Text", center.x/4 + 10, center.y-80, font.first,
                        font.second, "Welcome!", center.y / 5,
                        Colors::WHITE);
                scene.addObject(text);

                // Click to continue text
                std::shared_ptr<Object> text2 = std::make_shared<Text>(
                        "Click to Continue text", center.x/4 + 10, center.y+80, font.first,
                        font.second, "Click anywhere to continue", center.y / 10,
                        Colors::WHITE);
                scene.addObject(text2);

                // Click-to-continue function 
                std::shared_ptr<Command> command = std::make_shared<Command>(
                        [&scene, &window]() 
                        { 
                                createMainMenuScene(scene, window);
                        });

                // Click-to-continue rectangle
                std::shared_ptr<Rectangle> rect = std::make_shared<Rectangle>(
                        "Black Rectangle", topLeft.x, topLeft.y,
                        size.x, size.y, Colors::TRANSPARENT, command);
                scene.addClickableObject(rect); 
        }

        /*
        Create the main menu scene.

        @param scene Scene to create.
        @param window Window to render to.
        */
        void createMainMenuScene(Scene& scene, sf::RenderWindow& window)
        {
                LOG_TRACE("createMainMenuScene() called.");

                scene.clear();

                scene.name = "Main Menu";

                // Get necessary window information
                sf::Vector2i topLeft = getWindowTopLeftCorner();
                sf::Vector2u sizeU = getWindowSize(window);
                sf::Vector2i size(sizeU.x, sizeU.y);
                sf::Vector2i center = getWindowCenter(sizeU);

                // Sudoku title
                auto titleFont = getFont("title");
                std::shared_ptr<Object> title = std::make_shared<Text>(
                        "Text", center.x/2+100, -50, titleFont.first,
                        titleFont.second, "Sudoku", 280,
                        Colors::WHITE);
                scene.addObject(title);

        // New Game Button
                // New Game clickable black rectangle
                // New Game function 
                std::shared_ptr<Command> command = std::make_shared<Command>(
                        [&scene, &window]() 
                        { 
                                // TODO: createNewGameScene(scene, window);
                        });
        
                // New Game clickable black rectangle
                std::shared_ptr<Rectangle> newGameClickRect = std::make_shared<Rectangle>(
                        "New Game Clickable", center.x - 210, center.y - 100,
                        size.x/5 + 120, size.y/8, Colors::BLACK, command);
                scene.addClickableObject(newGameClickRect); 

                // New Game white rectangle
                std::shared_ptr<Object> newGameRect = std::make_shared<Rectangle>(
                        "New Game", center.x - 200, center.y - 90,
                        size.x/5 + 100, size.y/8 - 20, Colors::WHITE);
                scene.addObject(newGameRect);

                // New Game text
                auto font = getFont("font");
                std::shared_ptr<Object> newGameText = std::make_shared<Text>(
                        "New Game Text", center.x - 200, center.y - 100, font.first,
                        font.second, "New Game", center.y / 5,
                        Colors::BLACK);
                scene.addObject(newGameText);
        // Credits Button
                // Credits clickable black rectangle
                // Credits function 
                std::shared_ptr<Command> command2 = std::make_shared<Command>(
                        [&scene, &window]() 
                        {
                                createCreditsScene(scene, window);
                        });
                
                // Credits clickable black rectangle
                std::shared_ptr<Rectangle> creditsClickRect = std::make_shared<Rectangle>(
                        "New Game Clickable", center.x - 210, center.y + 20,      
                        size.x/5 + 120, size.y/8, Colors::BLACK, command2);
                scene.addClickableObject(creditsClickRect); 

                // Credits white rectangle
                std::shared_ptr<Object> creditsRect = std::make_shared<Rectangle>(
                        "Credits", center.x - 200, center.y + 30,
                        size.x/5 + 100, size.y/8 - 20, Colors::WHITE);
                scene.addObject(creditsRect);

                // Credits text
                std::shared_ptr<Object> creditsText = std::make_shared<Text>(
                        "Credits Text", center.x - 180, center.y + 20, font.first,
                        font.second, "Credits", center.y / 5,
                        Colors::BLACK);
                scene.addObject(creditsText);
        // Exit Button
                // Exit clickable black rectangle
                // Exit function 
                std::shared_ptr<Command> command3 = std::make_shared<Command>(
                        [&window]() 
                        {
                                window.close();
                        });
                
                // Exit clickable black rectangle
                std::shared_ptr<Rectangle> exitClickRect = std::make_shared<Rectangle>(
                        "Exit Clickable", center.x - 210, center.y + 140,      
                        size.x/5 + 120, size.y/8, Colors::BLACK, command3);
                scene.addClickableObject(exitClickRect); 

                // Exit white rectangle
                std::shared_ptr<Object> exitRect = std::make_shared<Rectangle>(
                        "Exit", center.x - 200, center.y + 150,
                        size.x/5 + 100, size.y/8 - 20, Colors::WHITE);
                scene.addObject(exitRect);

                // Exit text
                std::shared_ptr<Object> exitText = std::make_shared<Text>(
                        "Exit Text", center.x - 110, center.y + 140, font.first,
                        font.second, "Exit", center.y / 5,
                        Colors::BLACK);
                scene.addObject(exitText);
        }

        /*
        Create the credits scene.

        @param scene Scene to create.
        @param window Window to render to.
        */
        void createCreditsScene(Scene& scene, sf::RenderWindow& window)
        {
                LOG_TRACE("createCreditsScene() called.");

                scene.clear();

                scene.name = "Credits";

                // Get necessary window information
                sf::Vector2i topLeft = getWindowTopLeftCorner();
                sf::Vector2u sizeU = getWindowSize(window);
                sf::Vector2i size(sizeU.x, sizeU.y);
                sf::Vector2i center = getWindowCenter(sizeU);

                // Sudoku title
                auto titleFont = getFont("title");
                std::shared_ptr<Object> title = std::make_shared<Text>(
                        "Text", center.x/2+100, -50, titleFont.first,
                        titleFont.second, "Sudoku", 280,
                        Colors::WHITE);
                scene.addObject(title);

                // Credits text
                auto font = getFont("font");
                std::string credits = "Thank you for trying my sudoku game! ";
                credits += "I hope you are\nenjoying the game and that it has not caused\nyou too much stress. ";
                credits += "Please feel free to reach out to\nme with any feedback or suggestions. ";
                credits += "\n\n\t\t\t\t\t\tCreated by: github.com/Roiqk7";
                std::shared_ptr<Object> text = std::make_shared<Text>(
                        "Credits text", center.x/4 + 10, center.y - 80, font.first,
                        font.second, credits, center.y / 12,
                        Colors::WHITE);
                scene.addObject(text);

                // Click to return text
                std::shared_ptr<Object> text2 = std::make_shared<Text>(
                        "Click to return text", center.x/4 + 10, center.y + 160, font.first,
                        font.second, "Click anywhere to return", center.y / 10,
                        Colors::WHITE);
                scene.addObject(text2);

                // Click-to-return function 
                std::shared_ptr<Command> command = std::make_shared<Command>(
                        [&scene, &window]() 
                        { 
                                createMainMenuScene(scene, window);
                        });

                // Click-to-return rectangle
                std::shared_ptr<Rectangle> rect = std::make_shared<Rectangle>(
                        "Black Rectangle", topLeft.x, topLeft.y,
                        size.x, size.y, Colors::TRANSPARENT, command);
                scene.addClickableObject(rect); 
        }
// Game scenes
        /*
        Create the new game scene.

        @param scene Scene to create.
        @param window Window to render to.
        */
        void createNewGameScene(Scene& scene, sf::RenderWindow& window)
        {
                LOG_TRACE("createNewGameScene() called.");

                scene.clear();

                scene.name = "New Game";
        }

} // namespace System