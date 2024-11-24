/*
Date: 15/11/2024

This file contains pre-made scenes for the GUI.
*/

#include "../include/colors.hpp"
#include "../include/command.hpp"
#include "../include/gameHandler.hpp"
#include "../include/grid.hpp"
#include "../include/gui.hpp"
#include "../include/guiHelper.hpp"
#include "../include/macros.hpp"
#include "../include/object.hpp"
#include "../include/scene.hpp"
#include "../include/scenes.hpp"
#include "../include/soundEffect.hpp"
#include <chrono>
#include <filesystem>
#include <functional>
#include <iomanip>
#include <memory>
#include <sstream>
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
        @param gui Gui to add the scene to.
        */
        void createWelcomeScene(Scene& scene, GUI& gui)
        {
                LOG_TRACE("createWelcomeScene() called."); 

                scene.clear();

                scene.name = "Welcome";

                // Get necessary window information
                auto& window = gui.getWindow();
                sf::Vector2i topLeft = getWindowTopLeftCorner();
                sf::Vector2u sizeU = getWindowSize(window);
                sf::Vector2i size(sizeU.x, sizeU.y);
                sf::Vector2i center = getWindowCenter(sizeU);

                // Sudoku title
                auto titleFont = getFont("title");
                std::shared_ptr<Object> title = std::make_shared<Text>(
                        "Title", center.x/2+100, -50, titleFont.first,
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
                        [&scene, &gui]()
                        { 
                                createMainMenuScene(scene, gui);
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
        @param gui Gui to add the scene to.
        */
        void createMainMenuScene(Scene& scene, GUI& gui)
        {
                LOG_TRACE("createMainMenuScene() called.");

                scene.clear();

                scene.name = "Main Menu";

                // Get necessary window information
                auto& window = gui.getWindow();
                sf::Vector2i topLeft = getWindowTopLeftCorner();
                sf::Vector2u sizeU = getWindowSize(window);
                sf::Vector2i size(sizeU.x, sizeU.y);
                sf::Vector2i center = getWindowCenter(sizeU);

                // Sudoku title
                auto titleFont = getFont("title");
                std::shared_ptr<Object> title = std::make_shared<Text>(
                        "Title", center.x/2+100, -50, titleFont.first,
                        titleFont.second, "Sudoku", 280,
                        Colors::WHITE);
                scene.addObject(title);

        // New Game Button
                // New Game clickable black rectangle
                // New Game function 
                std::shared_ptr<Command> command = std::make_shared<Command>(
                        [&scene, &gui]()
                        { 
                                createNewGameScene(scene, gui);
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
                        [&scene, &gui]()
                        {
                                createCreditsScene(scene, gui);
                        });
                
                // Credits clickable black rectangle
                std::shared_ptr<Rectangle> creditsClickRect = std::make_shared<Rectangle>(
                        "Credits Clickable", center.x - 210, center.y + 20,
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
        @param gui Gui to add the scene to.
        */
        void createCreditsScene(Scene& scene, GUI& gui)
        {
                LOG_TRACE("createCreditsScene() called.");

                scene.clear();

                scene.name = "Credits";

                // Get necessary window information
                auto& window = gui.getWindow();
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
                credits += "I hope you are\nenjoying the game and that it has not caused you too\nmuch stress. ";
                credits += "Please feel free to reach out to me with\nany feedback or suggestions. ";
                credits += "\n\n\t\t\t\t\t\tCreated by: github.com/Roiqk7";
                std::shared_ptr<Object> text = std::make_shared<Text>(
                        "Credits text", center.x/4 + 10, center.y - 110, font.first,
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
                        [&scene, &gui]()
                        { 
                                createMainMenuScene(scene, gui);
                        });

                // Click-to-return rectangle
                std::shared_ptr<Rectangle> rect = std::make_shared<Rectangle>(
                        "Black Rectangle", topLeft.x, topLeft.y,
                        size.x, size.y, Colors::TRANSPARENT, command);
                scene.addClickableObject(rect); 
        }

        /*
        Create the help scene.

        @param scene Scene to create.
        @param gui Gui to add the scene to.
        */
        void createHelpScene(Scene& scene, GUI& gui)
        {
                LOG_TRACE("createHelpScene() called.");

                scene.clear();

                scene.name = "Help";

                // Get necessary window information
                auto& window = gui.getWindow();
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

                // Help text
                auto font = getFont("font");
                std::string help = "The objective is to fill a 9x9 grid with digits so that\n";
                help += "each column, each row, and each of the nine 3x3 subgrids\nthat ";
                help += "compose the grid (also called 'boxes', 'blocks', or\n'regions')";
                help += " contains all of the digits from 1 to 9.\n\nThe puzzle setter provides ";
                help += "a partially completed grid,\nwhich has a single solution.";
                std::shared_ptr<Object> text = std::make_shared<Text>(
                        "Help text", center.x/4 + 10, center.y - 110, font.first,
                        font.second, help, center.y / 12,
                        Colors::WHITE);
                scene.addObject(text);

                // Click to return text
                std::shared_ptr<Object> text2 = std::make_shared<Text>(
                        "Click to return text", center.x/4 + 10, center.y + 180, font.first,
                        font.second, "Click anywhere to return", center.y / 10,
                        Colors::WHITE);
                scene.addObject(text2);

                // Click-to-return function
                std::shared_ptr<Command> command = std::make_shared<Command>(
                        [&scene, &gui]()
                        {
                                createPauseScene(scene, gui);
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
        @param gui Gui to add the scene to.
        */
        void createNewGameScene(Scene& scene, GUI& gui)
        {
                LOG_TRACE("createNewGameScene() called.");

                scene.clear();

                scene.name = "New Game";

                // Get necessary window information
                auto& window = gui.getWindow();
                sf::Vector2i topLeft = getWindowTopLeftCorner();
                sf::Vector2u sizeU = getWindowSize(window);
                sf::Vector2i size(sizeU.x, sizeU.y);
                sf::Vector2i center = getWindowCenter(sizeU);

                // Sudoku title
                auto titleFont = getFont("title");
                std::shared_ptr<Object> title = std::make_shared<Text>(
                        "Title", center.x/2+100, -50, titleFont.first,
                        titleFont.second, "Sudoku", 280,
                        Colors::WHITE);
                scene.addObject(title);
        // Difficulty Buttons
        // Expert Difficulty Button
                // Expert Difficulty clickable black rectangle
                // Expert Difficulty function 
                std::shared_ptr<Command> command = std::make_shared<Command>(
                        [&scene, &gui]()
                        { 
                                auto& gameHandler = gui.getGameHandler();
                                gameHandler.newGame(Sudoku::Difficulty::EXPERT);
                                createGameScene(scene, gui);
                        });
        
                // Expert Difficulty clickable black rectangle
                std::shared_ptr<Rectangle> expertClickRect = std::make_shared<Rectangle>(
                        "Expert Difficulty Clickable", center.x - 160, center.y - 140,
                        size.x/5 + 50, size.y/8, Colors::BLACK, command);
                scene.addClickableObject(expertClickRect); 

                // Expert Difficulty white rectangle
                std::shared_ptr<Object> expertRect = std::make_shared<Rectangle>(
                        "Expert Difficulty", center.x - 150, center.y - 130,
                        size.x/5 + 30, size.y/8 - 20, Colors::RED);
                scene.addObject(expertRect);

                // Expert Difficulty text
                auto font = getFont("font");
                std::shared_ptr<Object> expertText = std::make_shared<Text>(
                        "Expert Difficulty Text", center.x - 140, center.y - 140, 
                        font.first, font.second, "Expert", center.y / 5,
                        Colors::BLACK);
                scene.addObject(expertText);
        // Hard Difficulty Button
                // Hard Difficulty clickable black rectangle
                // Hard Difficulty function 
                std::shared_ptr<Command> command2 = std::make_shared<Command>(
                        [&scene, &gui]()
                        {
                                auto& gameHandler = gui.getGameHandler();
                                gameHandler.newGame(Sudoku::Difficulty::HARD);
                                createGameScene(scene, gui);
                        });
                
                // Hard Difficulty clickable black rectangle
                std::shared_ptr<Rectangle> hardClickRect = std::make_shared<Rectangle>(
                        "Hard Difficulty Clickable", center.x - 160, center.y - 20,      
                        size.x/5 + 50, size.y/8, Colors::BLACK, command2);
                scene.addClickableObject(hardClickRect);

                // Hard Difficulty white rectangle
                std::shared_ptr<Object> hardRect = std::make_shared<Rectangle>(
                        "Hard Difficulty", center.x - 150, center.y - 10,
                        size.x/5 + 30, size.y/8 - 20, Colors::ORANGE);
                scene.addObject(hardRect);

                // Hard Difficulty text
                std::shared_ptr<Object> hardText = std::make_shared<Text>(
                        "Hard Difficulty Text", center.x - 95, center.y - 20, font.first,
                        font.second, "Hard", center.y / 5,
                        Colors::BLACK);
                scene.addObject(hardText);
        // Medium Difficulty Button
                // Medium Difficulty clickable black rectangle
                // Medium Difficulty function 
                std::shared_ptr<Command> command3 = std::make_shared<Command>(
                        [&scene, &gui]()
                        {
                                auto& gameHandler = gui.getGameHandler();
                                gameHandler.newGame(Sudoku::Difficulty::MEDIUM);
                                createGameScene(scene, gui);
                        });
                
                // Medium Difficulty clickable black rectangle
                std::shared_ptr<Rectangle> mediumClickRect = std::make_shared<Rectangle>(
                        "Medium Difficulty Clickable", center.x - 160, center.y + 100,      
                        size.x/5 + 50, size.y/8, Colors::BLACK, command3);
                scene.addClickableObject(mediumClickRect);

                // Medium Difficulty white rectangle
                std::shared_ptr<Object> mediumRect = std::make_shared<Rectangle>(
                        "Medium Difficulty", center.x - 150, center.y + 110,
                        size.x/5 + 30, size.y/8 - 20, Colors::YELLOW);
                scene.addObject(mediumRect);

                // Medium Difficulty text
                std::shared_ptr<Object> mediumText = std::make_shared<Text>(
                        "Medium Difficulty Text", center.x - 140, center.y + 100, font.first,
                        font.second, "Medium", center.y / 5,
                        Colors::BLACK);
                scene.addObject(mediumText);
        // Easy Difficulty Button
                // Easy Difficulty clickable black rectangle
                // Easy Difficulty function 
                std::shared_ptr<Command> command4 = std::make_shared<Command>(
                        [&scene, &gui]()
                        {
                                auto& gameHandler = gui.getGameHandler();
                                gameHandler.newGame(Sudoku::Difficulty::EASY);
                                createGameScene(scene, gui);
                        });
                
                // Easy Difficulty clickable black rectangle
                std::shared_ptr<Rectangle> easyClickRect = std::make_shared<Rectangle>(
                        "Easy Difficulty Clickable", center.x - 160, center.y + 220,      
                        size.x/5 + 50, size.y/8, Colors::BLACK, command4);
                scene.addClickableObject(easyClickRect);

                // Easy Difficulty white rectangle
                std::shared_ptr<Object> easyRect = std::make_shared<Rectangle>(
                        "Easy Difficulty", center.x - 150, center.y + 230,
                        size.x/5 + 30, size.y/8 - 20, Colors::GREEN);
                scene.addObject(easyRect);

                // Easy Difficulty text
                std::shared_ptr<Object> easyText = std::make_shared<Text>(
                        "Easy Difficulty Text", center.x - 95, center.y + 220, font.first,
                        font.second, "Easy", center.y / 5,
                        Colors::BLACK);
                scene.addObject(easyText);

        // Click to return box
                // Click-to-return function 
                std::shared_ptr<Command> commandR = std::make_shared<Command>(
                        [&scene, &gui]()
                        { 
                                createMainMenuScene(scene, gui);
                        });

                // Click-to-return rectangle
                std::shared_ptr<Rectangle> rect = std::make_shared<Rectangle>(
                        "Black Rectangle", topLeft.x, topLeft.y,
                        size.x, size.y, Colors::TRANSPARENT, commandR);
                scene.addClickableObject(rect); 
        }

        /*
        Create the game scene.

        @param scene Scene to create.
        @param gui Gui to add the scene to.
        */
        void createGameScene(Scene& scene, GUI& gui)
        {
                LOG_TRACE("createGameScene() called.");

                scene.clear();

                scene.name = "Game";

                // Get necessary window information
                auto& window = gui.getWindow();
                sf::Vector2i topLeft = getWindowTopLeftCorner();
                sf::Vector2u sizeU = getWindowSize(window);
                sf::Vector2i size(sizeU.x, sizeU.y);
                sf::Vector2i center = getWindowCenter(sizeU);
                // Get the game handler
                auto& gameHandler = gui.getGameHandler();
                // Get the font
                auto font = getFont("font");

                /*
                The game scene includes:
                        - sudoku board
                        - pause button
                        - difficulty level
                        - hint button
                        - mistakes counter
                        - timer
                        - notes switch
                        - panel with numbers
                */
        // Sudoku board
                // Actual sudoku board
                // Get the necessary grid information
                Sudoku::Grid grid;
                gameHandler.getGrid(grid);

                // Create the background frame
                std::shared_ptr<Object> gridBackgroundFrame = std::make_shared<Rectangle>(
                        "Grid Background", center.x - 370, topLeft.y + 80,
                        720, 720, Colors::WHITE);
                scene.addObject(gridBackgroundFrame);

                // Create the grid background
                const int GRID_SIZE = 680;
                const int GRID_X = center.x - 350;
                const int GRID_Y = topLeft.y + 100;
                std::shared_ptr<Object> gridBackground = std::make_shared<Rectangle>(
                        "Grid Background", GRID_X, GRID_Y,
                        GRID_SIZE, GRID_SIZE, Colors::NAVAJO_WHITE);
                scene.addObject(gridBackground);

                // Create the click function
                std::shared_ptr<Command> boardClickCommand = std::make_shared<Command>(
                        [&scene, &gui, GRID_SIZE, GRID_X, GRID_Y]()
                        {
                                sf::Event event = gui.getEvent();

                                if (event.type == sf::Event::MouseButtonPressed)
                                {
                                        return;
                                }

                                auto& gameHandler = gui.getGameHandler();
                                int selectedNumber = gameHandler.selectedNumber;

                                if (selectedNumber < 1 || selectedNumber > 9)
                                {
                                        return;
                                }

                                auto& window = gui.getWindow();
                                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                                int row = (mousePos.y - GRID_Y) / (GRID_SIZE / 9);
                                int col = (mousePos.x - GRID_X) / (GRID_SIZE / 9);

                                // Get the grid
                                Sudoku::Grid grid;
                                gameHandler.getGrid(grid);

                                // Check if the cell is empty
                                if (grid.getCell(row, col) == 0)
                                {
                                        auto& soundEffect = gui.getSoundEffect();

                                        if (!gameHandler.checkUserInput(row, col, selectedNumber))
                                        {
                                                // TODO: handle mistakes
                                                if (gameHandler.mistakes++ == 3)
                                                {
                                                        // TODO: handle game over
                                                }

                                                soundEffect.playSound("mistake");
                                        }
                                        // Correct input
                                        else
                                        {
                                                soundEffect.playSound("correct");
                                        }
                                        return createGameScene(scene, gui);
                                }
                        });

                // Create the clickable rectangle
                std::shared_ptr<Rectangle> clickableBoardRect = std::make_shared<Rectangle>(
                        "Clickable board rect", GRID_X, GRID_Y,
                        GRID_SIZE, GRID_SIZE, Colors::NAVAJO_WHITE,
                        boardClickCommand);
                scene.addClickableObject(clickableBoardRect);

                // Create the grid lines
                const int NUM_LINES = 9;
                const int LINE_SIZE = 2;
                // We temporarily store the thick lines to make sure they are rendered last
                std::array<std::shared_ptr<Object>, 4> thickLines;
                int thickLineIndex = 0;
                for (int i = 1; i < NUM_LINES; i++)
                {
                        int offset = (GRID_SIZE / NUM_LINES) * i - LINE_SIZE / 2;
                        bool thickLine = i % 3 == 0;
                        // Determine the color of the line
                        sf::Color color = thickLine ? Colors::LIGHT_SKY_BLUE
                                : Colors::WHITE;

                        // Horizontal lines
                        std::shared_ptr<Object> lineH = std::make_shared<Rectangle>(
                                "Grid Line Horizontal",
                                GRID_X, GRID_Y + offset,
                                GRID_SIZE, LINE_SIZE, color);
                        if (thickLine)
                        {
                                thickLines[thickLineIndex++] = lineH;
                        }
                        else
                        {
                                scene.addObject(lineH);
                        }

                        // Vertical lines
                        std::shared_ptr<Object> lineV = std::make_shared<Rectangle>(
                                "Grid Line Vertical",
                                GRID_X + offset, GRID_Y,
                                LINE_SIZE, GRID_SIZE, color);

                        if (thickLine)
                        {
                                thickLines[thickLineIndex++] = lineV;
                        }
                        else
                        {
                                scene.addObject(lineV);
                        }
                }
                // Add the thick lines
                for (const auto& line : thickLines)
                {
                        scene.addObject(line);
                }

                // Create the numbers
                const int NUM_SIZE = 70;
                const int NUM_OFFSET = 80;

                for (int row = 0; row < 9; row++)
                {
                        for (int col = 0; col < 9; col++)
                        {
                                int num = grid.getCell(row, col);
                                if (num != 0)
                                {
                                        std::string numStr = std::to_string(num);
                                        std::shared_ptr<Object> number = std::make_shared<Text>(
                                                "numStr",
                                                GRID_X + 12 + col * NUM_OFFSET - col * (NUM_OFFSET / 20),
                                                GRID_Y - 8 + row * NUM_OFFSET - row * (NUM_OFFSET / 20),
                                                font.first, font.second,
                                                numStr, NUM_SIZE, Colors::WHITE);
                                        scene.addObject(number);
                                }
                        }
                }
        // Pause Button
                // Pause function
                std::shared_ptr<Command> command = std::make_shared<Command>(
                        [&scene, &gui]()
                        {
                                createPauseScene(scene, gui);
                        });

                // Pause clickable rectangle
                std::shared_ptr<Rectangle> pauseClickRect = std::make_shared<Rectangle>(
                        "Pause Clickable", GRID_X, topLeft.y + 10,
                        60, 60, Colors::WHITE, command);
                scene.addClickableObject(pauseClickRect);

                // Pause symbol rectangles
                std::shared_ptr<Object> pauseRect1 = std::make_shared<Rectangle>(
                        "Pause 1", GRID_X + 5, topLeft.y + 15,
                        20, 50, Colors::BLACK);
                scene.addObject(pauseRect1);

                std::shared_ptr<Object> pauseRect2 = std::make_shared<Rectangle>(
                        "Pause 2", GRID_X + 35, topLeft.y + 15,
                        20, 50, Colors::BLACK);
                scene.addObject(pauseRect2);
        // Difficulty Level
                // Get the difficulty level
                Sudoku::Difficulty difficulty = gameHandler.difficulty;
                std::string difficultyStr = "Difficulty: ";

                switch (difficulty)
                {
                        case Sudoku::Difficulty::EASY:
                                difficultyStr += "Easy";
                                break;
                        case Sudoku::Difficulty::MEDIUM:
                                difficultyStr += "Medium";
                                break;
                        case Sudoku::Difficulty::HARD:
                                difficultyStr += "Hard";
                                break;
                        case Sudoku::Difficulty::EXPERT:
                                difficultyStr += "Expert";
                                break;
                        default:
                                difficultyStr += "??????";
                                LOG_ERROR("Unknown difficulty level.");
                                break;
                }

                // Difficulty text
                std::shared_ptr<Object> difficultyText = std::make_shared<Text>(
                        "Difficulty Text", center.x - 250, topLeft.y + 10, font.first,
                        font.second, difficultyStr, 50,
                        Colors::WHITE);
                scene.addObject(difficultyText);

        // TODO: other elements

        // Number Panel
                // Number panel frame
                std::shared_ptr<Object> numberPanelFrame = std::make_shared<Rectangle>(
                        "Number Panel Frame",
                        GRID_X + GRID_SIZE + 30, center.y - 120,
                        320, 320, Colors::WHITE);
                scene.addObject(numberPanelFrame);

                // Number panel background
                const int NUM_PANEL_SIZE = 300;
                const int NUM_PANEL_X = GRID_X + GRID_SIZE + 40;
                const int NUM_PANEL_Y = center.y - 110;
                std::shared_ptr<Object> numberPanelBackground = std::make_shared<Rectangle>(
                        "Number Panel Background",
                        NUM_PANEL_X, NUM_PANEL_Y,
                        NUM_PANEL_SIZE, NUM_PANEL_SIZE,
                        Colors::NAVAJO_WHITE);
                scene.addObject(numberPanelBackground);

                // Number panel click function
                std::shared_ptr<Command> numberPanelClickCommand = std::make_shared<Command>(
                        [&scene, &gui, NUM_PANEL_SIZE, NUM_PANEL_X, NUM_PANEL_Y]()
                        {
                                sf::Event event = gui.getEvent();

                                if (event.type == sf::Event::MouseButtonPressed)
                                {
                                        return;
                                }

                                auto& window = gui.getWindow();
                                auto& gameHandler = gui.getGameHandler();
                                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                                int row = (mousePos.y - NUM_PANEL_Y) / (NUM_PANEL_SIZE / 3);
                                int col = (mousePos.x - NUM_PANEL_X) / (NUM_PANEL_SIZE / 3);

                                /*
                                Layout:
                                        1 2 3
                                        4 5 6
                                        7 8 9
                                */
                                int num = row * 3 + col + 1;

                                gameHandler.selectedNumber = num;

                                LOG_TRACE("Selected number: " + std::to_string(num));
                        });

                // Number panel clickable rectangle
                std::shared_ptr<Rectangle> numberPanelClickableRect = std::make_shared<Rectangle>(
                        "Number Panel Clickable",
                        GRID_X + GRID_SIZE + 40, center.y - 110,
                        NUM_PANEL_SIZE, NUM_PANEL_SIZE,
                        Colors::TRANSPARENT, numberPanelClickCommand);
                scene.addClickableObject(numberPanelClickableRect);

                // Number panel lines
                const int NUM_PANEL_NUM_LINES = 3;
                const int NUM_PANEL_LINE_SIZE = 2;

                for (int i = 1; i < NUM_PANEL_NUM_LINES; i++)
                {
                        int offset = (NUM_PANEL_SIZE / NUM_PANEL_NUM_LINES) * i - NUM_PANEL_LINE_SIZE / 2;

                        // Horizontal lines
                        std::shared_ptr<Object> lineH = std::make_shared<Rectangle>(
                                "Number Panel Line Horizontal",
                                GRID_X + GRID_SIZE + 40, center.y - 110 + offset,
                                NUM_PANEL_SIZE, NUM_PANEL_LINE_SIZE, Colors::WHITE);
                        scene.addObject(lineH);

                        // Vertical lines
                        std::shared_ptr<Object> lineV = std::make_shared<Rectangle>(
                                "Number Panel Line Vertical",
                                GRID_X + GRID_SIZE + 40 + offset, center.y - 110,
                                NUM_PANEL_LINE_SIZE, NUM_PANEL_SIZE, Colors::WHITE);
                        scene.addObject(lineV);
                }

                // Number panel numbers
                const int NUM_PANEL_NUM_SIZE = 100;
                const int NUM_PANEL_NUM_OFFSET = 100;

                for (int row = 0; row < 3; row++)
                {
                        for (int col = 0; col < 3; col++)
                        {
                                int num = row * 3 + col + 1;
                                std::string numStr = std::to_string(num);
                                std::shared_ptr<Object> number = std::make_shared<Text>(
                                        "Number Panel Number",
                                        GRID_X + GRID_SIZE + 60 + col * NUM_PANEL_NUM_OFFSET,
                                        center.y - 120 + row * NUM_PANEL_NUM_OFFSET,
                                        font.first, font.second,
                                        numStr, NUM_PANEL_NUM_SIZE, Colors::WHITE);
                                scene.addObject(number);
                        }
                }
        }

        /*
        Create the pause scene.

        @param scene Scene to create.
        @param gui Gui to add the scene to.
        */
        void createPauseScene(Scene& scene, GUI& gui)
        {
                LOG_TRACE("createPauseScene() called.");

                scene.clear();

                scene.name = "Pause";

                // Get necessary window information
                auto& window = gui.getWindow();
                sf::Vector2i topLeft = getWindowTopLeftCorner();
                sf::Vector2u sizeU = getWindowSize(window);
                sf::Vector2i size(sizeU.x, sizeU.y);
                sf::Vector2i center = getWindowCenter(sizeU);

                // Sudoku title
                auto titleFont = getFont("title");
                std::shared_ptr<Object> title = std::make_shared<Text>(
                        "Title", center.x/2+100, -50, titleFont.first,
                        titleFont.second, "Sudoku", 280,
                        Colors::WHITE);
                scene.addObject(title);

        // Resume Button
                // Resume clickable black rectangle
                // Resume function
                std::shared_ptr<Command> command = std::make_shared<Command>(
                        [&scene, &gui]()
                        {
                                createGameScene(scene, gui);
                        });

                // Resume clickable black rectangle
                std::shared_ptr<Rectangle> resumeClickRect = std::make_shared<Rectangle>(
                        "Resume Clickable", center.x - 210, center.y - 100,
                        size.x/5 + 120, size.y/8, Colors::BLACK, command);
                scene.addClickableObject(resumeClickRect);

                // Resume white rectangle
                std::shared_ptr<Object> resumeRect = std::make_shared<Rectangle>(
                        "Resume", center.x - 200, center.y - 90,
                        size.x/5 + 100, size.y/8 - 20, Colors::WHITE);
                scene.addObject(resumeRect);

                // Resume text
                auto font = getFont("font");
                std::shared_ptr<Object> newGameText = std::make_shared<Text>(
                        "Resume Text", center.x - 160, center.y - 100, font.first,
                        font.second, "Resume", center.y / 5,
                        Colors::BLACK);
                scene.addObject(newGameText);
        // Help Button
                // Help clickable black rectangle
                // Help function
                std::shared_ptr<Command> command2 = std::make_shared<Command>(
                        [&scene, &gui]()
                        {
                                createHelpScene(scene, gui);
                        });

                // Help clickable black rectangle
                std::shared_ptr<Rectangle> helpClickRect = std::make_shared<Rectangle>(
                        "Help Clickable", center.x - 210, center.y + 20,
                        size.x/5 + 120, size.y/8 + 5, Colors::BLACK, command2);
                scene.addClickableObject(helpClickRect);

                // Help white rectangle
                std::shared_ptr<Object> helpRect = std::make_shared<Rectangle>(
                        "Help", center.x - 200, center.y + 30,
                        size.x/5 + 100, size.y/8 - 15, Colors::WHITE);
                scene.addObject(helpRect);

                // Help text
                std::shared_ptr<Object> helpText = std::make_shared<Text>(
                        "Help Text", center.x - 110, center.y + 20, font.first,
                        font.second, "Help", center.y / 5,
                        Colors::BLACK);
                scene.addObject(helpText);
        // Exit Button
                // Exit clickable black rectangle
                // Exit function
                std::shared_ptr<Command> command3 = std::make_shared<Command>(
                        [&scene, &gui]()
                        {
                                createMainMenuScene(scene, gui);
                        });

                // Exit clickable black rectangle
                std::shared_ptr<Rectangle> exitClickRect = std::make_shared<Rectangle>(
                        "Exit Clickable", center.x - 210, center.y + 145,
                        size.x/5 + 120, size.y/8, Colors::BLACK, command3);
                scene.addClickableObject(exitClickRect);

                // Exit white rectangle
                std::shared_ptr<Object> exitRect = std::make_shared<Rectangle>(
                        "Exit", center.x - 200, center.y + 155,
                        size.x/5 + 100, size.y/8 - 20, Colors::WHITE);
                scene.addObject(exitRect);

                // Exit text
                std::shared_ptr<Object> exitText = std::make_shared<Text>(
                        "Exit Text", center.x - 110, center.y + 145, font.first,
                        font.second, "Exit", center.y / 5,
                        Colors::BLACK);
                scene.addObject(exitText);
        }
// Development scenes
        /*
        Create the execution time scene.

        @param scene Scene to create.
        @param gui Gui to add the scene to.
        @param time Execution time in microseconds.

        @note Displays the time of the GUI::handleEvent() function.
        */
        void createExecutionTimeScene(Scene& scene, GUI& gui,
                const std::chrono::microseconds& time)
        {
                LOG_TRACE("createExecutionTimeScene() called.");

                scene.clear();

                scene.name = "Execution Time";

                // Get necessary window information
                auto& window = gui.getWindow();
                sf::Vector2u sizeU = getWindowSize(window);
                sf::Vector2i bottomRight = getWindowBottomRightCorner(sizeU);

                // Execution time text
                auto font = getFont("font");
                std::string timeStr = "Execution time:";

                auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(time).count();
                if (microseconds < 1000000)
                {
                        std::stringstream ss;
                        ss << std::fixed << std::setprecision(3) << std::setw(7) << std::setfill(' ') << (microseconds / 1000.0);
                        timeStr += ss.str() + " ms";
                }
                else
                {
                        timeStr += " > 1 s";
                }

                std::shared_ptr<Object> text = std::make_shared<Text>(
                        "Execution Time", bottomRight.x - 310, bottomRight.y - 30,
                        font.first, font.second, timeStr, 20,
                        Colors::WHITE);
                scene.addObject(text);
        }
} // namespace System