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
#include <array>
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
#include <tuple>
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

                auto wi = getWindowInfo(window);

                auto button = createButton("Button",
                        wi.topLeft.x, wi.topLeft.y,
                        wi.size.x, wi.size.y, wi.size.x / 10,
                        Colors::BLACK, Colors::SHADOW);
                scene.addObject(button.frame);
                scene.addObject(button.background);

                // Text
                auto font = getFont("font");
                scene.addObject(std::make_shared<Text>(
                        "Text", wi.center.x/4 + 10, wi.center.y-80, font.first,
                        font.second, "THIS SHOULD BE HIDDEN", wi.center.y / 5,
                        Colors::WHITE));
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

                auto wi = getWindowInfo(window);

                // Background
                std::shared_ptr<Object> background = std::make_shared<Rectangle>(
                        "Background", wi.topLeft.x, wi.topLeft.y,
                        wi.size.x, wi.size.y, Colors::LIGHT_SKY_BLUE);
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

                sf::RenderWindow& window = gui.getWindow();
                auto wi = getWindowInfo(window);

                // Sudoku title
                scene.addObject(getTitle(window));

                // Welcome text
                auto font = getFont("font");
                std::shared_ptr<Object> text = std::make_shared<Text>(
                        "Text", wi.center.x/4 + 10, wi.center.y-80, font.first,
                        font.second, "Welcome!", wi.center.y / 5,
                        Colors::WHITE);
                scene.addObject(text);

                // Click to continue text
                std::shared_ptr<Object> text2 = std::make_shared<Text>(
                        "Click to Continue text", wi.center.x/4 + 10, wi.center.y+80, font.first,
                        font.second, "Click anywhere to continue", wi.center.y / 10,
                        Colors::WHITE);
                scene.addObject(text2);

                // Click-to-continue function 
                std::shared_ptr<Command> command = std::make_shared<Command>(
                        [&scene, &gui]()
                        { 
                                createMainMenuScene(scene, gui);
                        });
                scene.addClickableObject(createClickToContinue(command, window));
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

                sf::RenderWindow& window = gui.getWindow();
                auto wi = getWindowInfo(window);

                // Sudoku title
                scene.addObject(getTitle(window));

        // New Game Button
                // New Game clickable black rectangle
                // New Game function 
                std::shared_ptr<Command> command = std::make_shared<Command>(
                        [&scene, &gui]()
                        { 
                                createNewGameScene(scene, gui);
                        });

                auto NGButton = createButton("New Game", wi.center.x - 210, wi.center.y - 100,
                        wi.size.x/5 + 120, wi.size.y/8, 10, Colors::BLACK, Colors::WHITE, command);

                scene.addObject(NGButton.frame);
                scene.addClickableObject(NGButton.clickable);
                scene.addObject(NGButton.background);

                // New Game text
                auto font = getFont("font");
                scene.addObject(std::make_shared<Text>(
                        "New Game Text", wi.center.x - 200, wi.center.y - 100, font.first,
                        font.second, "New Game", wi.center.y / 5,
                        Colors::BLACK));
        // Credits Button
                // Credits clickable black rectangle
                // Credits function 
                std::shared_ptr<Command> command2 = std::make_shared<Command>(
                        [&scene, &gui]()
                        {
                                createCreditsScene(scene, gui);
                        });

                auto creditsButton = createButton("Credits", wi.center.x - 210, wi.center.y + 20,
                        wi.size.x/5 + 120, wi.size.y/8, 10, Colors::BLACK, Colors::WHITE, command2);
                scene.addObject(creditsButton.frame);
                scene.addClickableObject(creditsButton.clickable);
                scene.addObject(creditsButton.background);

                // Credits text
                scene.addObject(std::make_shared<Text>(
                        "Credits Text", wi.center.x - 180, wi.center.y + 20, font.first,
                        font.second, "Credits", wi.center.y / 5,
                        Colors::BLACK));
        // Exit Button
                // Exit clickable black rectangle
                // Exit function 
                std::shared_ptr<Command> command3 = std::make_shared<Command>(
                        [&window]() 
                        {
                                window.close();
                        });

                auto exitButton = createButton("Exit", wi.center.x - 210, wi.center.y + 140,
                        wi.size.x/5 + 120, wi.size.y/8, 10, Colors::BLACK, Colors::WHITE, command3);
                scene.addObject(exitButton.frame);
                scene.addClickableObject(exitButton.clickable);
                scene.addObject(exitButton.background);

                // Exit text
                scene.addObject(std::make_shared<Text>(
                        "Exit Text", wi.center.x - 110, wi.center.y + 140, font.first,
                        font.second, "Exit", wi.center.y / 5,
                        Colors::BLACK));
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

                sf::RenderWindow& window = gui.getWindow();
                auto wi = getWindowInfo(window);

                // Sudoku title
                scene.addObject(getTitle(window));

                // Credits text
                auto font = getFont("font");
                std::string credits = "Thank you for trying my sudoku game! ";
                credits += "I hope you are\nenjoying the game and that it has not caused you too\nmuch stress. ";
                credits += "Please feel free to reach out to me with\nany feedback or suggestions. ";
                credits += "\n\n\t\t\t\t\t\tCreated by: github.com/Roiqk7";
                scene.addObject(std::make_shared<Text>(
                        "Credits text", wi.center.x/4 + 10, wi.center.y - 110, font.first,
                        font.second, credits, wi.center.y / 12,
                        Colors::WHITE));

                // Click to return text
                scene.addObject(std::make_shared<Text>(
                        "Click to return text", wi.center.x/4 + 10, wi.center.y + 160, font.first,
                        font.second, "Click anywhere to return", wi.center.y / 10,
                        Colors::WHITE));

                // Click-to-return function 
                std::shared_ptr<Command> command = std::make_shared<Command>(
                        [&scene, &gui]()
                        { 
                                createMainMenuScene(scene, gui);
                        });
                // Click-to-return rectangle
                scene.addClickableObject(createClickToContinue(command, window));
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

                sf::RenderWindow& window = gui.getWindow();
                auto wi = getWindowInfo(window);

                // Sudoku title
                scene.addObject(getTitle(window));

                // Help text
                auto font = getFont("font");
                std::string help = "The objective is to fill a 9x9 grid with digits so that\n";
                help += "each column, each row, and each of the nine 3x3 subgrids\nthat ";
                help += "compose the grid (also called 'boxes', 'blocks', or\n'regions')";
                help += " contains all of the digits from 1 to 9.\n\nThe puzzle setter provides ";
                help += "a partially completed grid,\nwhich has a single solution.";
                scene.addObject(std::make_shared<Text>(
                        "Help text", wi.center.x/4 + 10, wi.center.y - 110, font.first,
                        font.second, help, wi.center.y / 12,
                        Colors::WHITE));

                // Click to return text
                scene.addObject(std::make_shared<Text>(
                        "Click to return text", wi.center.x/4 + 10, wi.center.y + 180, font.first,
                        font.second, "Click anywhere to return", wi.center.y / 10,
                        Colors::WHITE));

                // Click-to-return function
                std::shared_ptr<Command> command = std::make_shared<Command>(
                        [&scene, &gui]()
                        {
                                createPauseScene(scene, gui);
                        });

                // Click-to-return rectangle
                scene.addClickableObject(createClickToContinue(command, window));
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

                sf::RenderWindow& window = gui.getWindow();
                auto wi = getWindowInfo(window);

                // Sudoku title
                scene.addObject(getTitle(window));

        // Difficulty Buttons
        std::array<std::tuple<std::string,
                Sudoku::Difficulty, sf::Color>, 4> diffMap =
                {
                        std::make_tuple("Expert",
                                Sudoku::Difficulty::EXPERT, Colors::RED),
                        std::make_tuple("Hard",
                                Sudoku::Difficulty::HARD, Colors::ORANGE),
                        std::make_tuple("Medium",
                                Sudoku::Difficulty::MEDIUM, Colors::YELLOW),
                        std::make_tuple("Easy",
                                Sudoku::Difficulty::EASY, Colors::GREEN)
        };

        for (int i = 0; i < 4; i++)
        {
                auto& diffTuple = diffMap[i];
                auto& diffName = std::get<0>(diffTuple);
                auto& diff = std::get<1>(diffTuple);
                auto& diffColor = std::get<2>(diffTuple);

                auto command = [&scene, &gui, diff]()
                {
                        auto& gameHandler = gui.getGameHandler();
                        gameHandler.newGame(diff);
                        createGameScene(scene, gui);
                };

                auto button = createButton(
                        diffName + " Difficulty Button",
                        wi.center.x - 160, wi.center.y - 140 + 120 * i,
                        wi.size.x/5 + 50, wi.size.y/8, 10,
                        Colors::BLACK, diffColor,
                        std::make_shared<Command>(command));
                scene.addObject(button.frame);
                scene.addClickableObject(button.clickable);
                scene.addObject(button.background);
        }

        // Difficulty Texts
        auto font = getFont("font");
        // Expert Difficulty text
        scene.addObject(std::make_shared<Text>(
                "Expert Difficulty Text", wi.center.x - 140,
                wi.center.y - 140, font.first,
                font.second, "Expert", wi.center.y / 5,
                Colors::BLACK));

        // Hard Difficulty text
        scene.addObject(std::make_shared<Text>(
                "Hard Difficulty Text", wi.center.x - 95,
                wi.center.y - 20, font.first,
                font.second, "Hard", wi.center.y / 5,
                Colors::BLACK));

        // Medium Difficulty text
        scene.addObject(std::make_shared<Text>(
                "Medium Difficulty Text", wi.center.x - 140,
                wi.center.y + 100, font.first,
                font.second, "Medium", wi.center.y / 5,
                Colors::BLACK));

        // Easy Difficulty text
        scene.addObject(std::make_shared<Text>(
                "Easy Difficulty Text", wi.center.x - 95,
                wi.center.y + 220, font.first,
                font.second, "Easy", wi.center.y / 5,
                Colors::BLACK));

        // Click to return box
                // Click-to-return function 
                std::shared_ptr<Command> commandR = std::make_shared<Command>(
                        [&scene, &gui]()
                        { 
                                createMainMenuScene(scene, gui);
                        });
                scene.addClickableObject(createClickToContinue(commandR, window));
        }

        /*
        Create the game scene.

        @param scene Scene to create.
        @param gui Gui to add the scene to.
        */
        void createGameScene(Scene& scene, GUI& gui)
        {
                // TODO: Simplify as other scenes

                LOG_TRACE("createGameScene() called.");

                scene.clear();

                scene.name = "Game";

                sf::RenderWindow& window = gui.getWindow();
                auto wi = getWindowInfo(window);

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

                // Create the grid background
                const int GRID_SIZE = 680;
                const int GRID_X = wi.center.x - 350;
                const int GRID_Y = wi.topLeft.y + 100;
                const int FRAME_MARGIN = 20;

                // Create the click function
                std::shared_ptr<Command> boardClickCommand = std::make_shared<Command>(
                        [&scene, &gui, GRID_SIZE, GRID_X, GRID_Y]()
                        {
                                sf::Event event = gui.getEvent();

                                // Ignore if not a mouse click
                                // Should not happen
                                if (event.type != sf::Event::MouseButtonPressed)
                                {
                                        LOG_WARN("Ignoring non-mouse click event. This log message should not appear.");
                                        return;
                                }

                                auto& gameHandler = gui.getGameHandler();
                                int selectedNumber = gameHandler.selectedNumber;

                                // Check if the selected number is valid
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

                                // Validate the row and column
                                // Note: row and col should be in the range [0, 8]
                                if (!grid.checkIndex(grid.convertIndex(row, col)))
                                {
                                        LOG_WARN("Invalid row x col: {} x {} (index: {}. This log message should not appear.",
                                                row, col, grid.convertIndex(row, col));
                                        return;
                                }

                                // Check if the cell is empty
                                if (grid.getCell(row, col) == 0)
                                {
                                        auto& soundEffect = gui.getSoundEffect();

                                        if (!gameHandler.checkUserInput(row, col, selectedNumber))
                                        {
                                                soundEffect.playSound("mistake");

                                                // TODO: handle mistakes
                                                if (++gameHandler.mistakes == 3)
                                                {
                                                        return createGameOverScene(scene, gui, false);
                                                }
                                        }
                                        // Correct input
                                        else
                                        {
                                                soundEffect.playSound("correct");

                                                // Check win condition
                                                if (gameHandler.checkWin())
                                                {
                                                        return createGameOverScene(scene, gui, true);
                                                }
                                        }
                                        return createGameScene(scene, gui);
                                }
                        });

                auto& sudokuGrid = createButton("Grid",
                        GRID_X - FRAME_MARGIN, GRID_Y - FRAME_MARGIN,
                        GRID_SIZE + 2 * FRAME_MARGIN, GRID_SIZE + 2 * FRAME_MARGIN,
                        FRAME_MARGIN,
                        Colors::WHITE, Colors::NAVAJO_WHITE,
                        boardClickCommand);
                scene.addObject(sudokuGrid.frame);
                scene.addClickableObject(sudokuGrid.clickable);
                scene.addObject(sudokuGrid.background);

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

                        // Vertical lines
                        std::shared_ptr<Object> lineV = std::make_shared<Rectangle>(
                                "Grid Line Vertical",
                                GRID_X + offset, GRID_Y,
                                LINE_SIZE, GRID_SIZE, color);

                        if (thickLine)
                        {
                                thickLines[thickLineIndex++] = lineH;
                                thickLines[thickLineIndex++] = lineV;
                        }
                        else
                        {
                                scene.addObject(lineH);
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

                // Render the numbers
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
                        "Pause Clickable", GRID_X, wi.topLeft.y + 10,
                        60, 60, Colors::WHITE, command);
                scene.addClickableObject(pauseClickRect);

                // Pause symbol rectangles
                std::shared_ptr<Object> pauseRect1 = std::make_shared<Rectangle>(
                        "Pause 1", GRID_X + 5, wi.topLeft.y + 15,
                        20, 50, Colors::BLACK);
                scene.addObject(pauseRect1);

                std::shared_ptr<Object> pauseRect2 = std::make_shared<Rectangle>(
                        "Pause 2", GRID_X + 35, wi.topLeft.y + 15,
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
                        "Difficulty Text",
                        wi.center.x - 250, wi.topLeft.y + 10,
                        font.first, font.second, difficultyStr, 50,
                        Colors::WHITE);
                scene.addObject(difficultyText);
        // Score label
                // Score text
                std::shared_ptr<Object> scoreText = std::make_shared<Text>(
                        "Score Text",
                        GRID_X + GRID_SIZE + FRAME_MARGIN, GRID_Y - FRAME_MARGIN - 60,
                        font.first, font.second,
                        "Score: " + std::to_string(gameHandler.score), 40,
                        Colors::WHITE);
                scene.addObject(scoreText);

        // Number Panel
                // Number panel frame
                std::shared_ptr<Object> numberPanelFrame = std::make_shared<Rectangle>(
                        "Number Panel Frame",
                        GRID_X + GRID_SIZE + 30, wi.center.y - 120,
                        320, 320, Colors::WHITE);
                scene.addObject(numberPanelFrame);

                // Number panel background
                const int NUM_PANEL_SIZE = 300;
                const int NUM_PANEL_X = GRID_X + GRID_SIZE + 40;
                const int NUM_PANEL_Y = wi.center.y - 110;
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

                                // Ignore if not a mouse click
                                // Should not happen
                                if (event.type != sf::Event::MouseButtonPressed)
                                {
                                        LOG_WARN("Ignoring non-mouse click event. This log message should not appear.");
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
                        GRID_X + GRID_SIZE + 40, wi.center.y - 110,
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
                                GRID_X + GRID_SIZE + 40, wi.center.y - 110 + offset,
                                NUM_PANEL_SIZE, NUM_PANEL_LINE_SIZE, Colors::WHITE);
                        scene.addObject(lineH);

                        // Vertical lines
                        std::shared_ptr<Object> lineV = std::make_shared<Rectangle>(
                                "Number Panel Line Vertical",
                                GRID_X + GRID_SIZE + 40 + offset, wi.center.y - 110,
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
                                        wi.center.y - 120 + row * NUM_PANEL_NUM_OFFSET,
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

                sf::RenderWindow& window = gui.getWindow();
                auto wi = getWindowInfo(window);

                // Sudoku title
                scene.addObject(getTitle(window));

        // Resume Button
                // Resume clickable black rectangle
                // Resume function
                std::shared_ptr<Command> command = std::make_shared<Command>(
                        [&scene, &gui]()
                        {
                                createGameScene(scene, gui);
                        });

                auto& resumeButton = createButton("Resume",
                        wi.center.x - 210, wi.center.y - 100,
                        wi.size.x/5 + 120, wi.size.y/8, 10,
                        Colors::BLACK, Colors::WHITE, command);
                scene.addObject(resumeButton.frame);
                scene.addClickableObject(resumeButton.clickable);
                scene.addObject(resumeButton.background);

                // Resume text
                auto font = getFont("font");
                scene.addObject(std::make_shared<Text>(
                        "Resume Text", wi.center.x - 160, wi.center.y - 100,
                        font.first, font.second, "Resume", wi.center.y / 5,
                        Colors::BLACK));
        // Help Button
                // Help clickable black rectangle
                // Help function
                std::shared_ptr<Command> command2 = std::make_shared<Command>(
                        [&scene, &gui]()
                        {
                                createHelpScene(scene, gui);
                        });

                auto& helpButton = createButton("Help",
                        wi.center.x - 210, wi.center.y + 20,
                        wi.size.x/5 + 120, wi.size.y/8 + 5, 10,
                        Colors::BLACK, Colors::WHITE, command2);
                scene.addObject(helpButton.frame);
                scene.addClickableObject(helpButton.clickable);
                scene.addObject(helpButton.background);

                // Help text
                scene.addObject(std::make_shared<Text>(
                        "Help Text", wi.center.x - 110, wi.center.y + 20, font.first,
                        font.second, "Help", wi.center.y / 5,
                        Colors::BLACK));
        // Exit Button
                // Exit clickable black rectangle
                // Exit function
                std::shared_ptr<Command> command3 = std::make_shared<Command>(
                        [&scene, &gui]()
                        {
                                createMainMenuScene(scene, gui);
                        });

                auto& exitButton = createButton("Exit",
                        wi.center.x - 210, wi.center.y + 145,
                        wi.size.x/5 + 120, wi.size.y/8, 10,
                        Colors::BLACK, Colors::WHITE, command3);
                scene.addObject(exitButton.frame);
                scene.addClickableObject(exitButton.clickable);
                scene.addObject(exitButton.background);

                // Exit text
                std::shared_ptr<Object> exitText = std::make_shared<Text>(
                        "Exit Text", wi.center.x - 110, wi.center.y + 145,
                        font.first, font.second, "Exit", wi.center.y / 5,
                        Colors::BLACK);
                scene.addObject(exitText);
        }

        /*
        Create the game over scene.

        @param scene Scene to create.
        @param gui Gui to add the scene to.
        @param win True if the player won, false otherwise.
        */
        void createGameOverScene(Scene& scene, GUI& gui, bool win)
        {
                LOG_TRACE("createGameOverScene() called.");

                const std::string result = win ? "Won" : "Lost";
                LOG_DEBUG("Game result: Player " + result);

                scene.clear();

                scene.name = "Game Over";

                sf::RenderWindow& window = gui.getWindow();
                auto wi = getWindowInfo(window);

                // Sudoku title
                scene.addObject(getTitle(window));

                const int X_POS = wi.center.x - 250;
                const int Y_POS = wi.topLeft.y + 260;
                const int X_SIZE = wi.topLeft.x + 500;
                const int Y_SIZE = wi.topLeft.y + 510;

        // Background
                auto& background = createButton("Background",
                        X_POS, Y_POS,
                        X_SIZE, Y_SIZE,
                        10, Colors::WHITE, Colors::NAVAJO_WHITE);
                scene.addObject(background.frame);
                scene.addObject(background.background);
        // Text
                // Format information
                auto& gameHandler = gui.getGameHandler();
                std::string timeStr = getFormattedTime(gameHandler.time);
                std::string difficultyStr = getFormattedDifficulty(gameHandler.difficulty);

                // Information vector
                std::vector<std::pair<std::string, std::string>> gameOverInfo = {
                        {"Result", result},
                        {"Difficulty", difficultyStr},
                        {"Score", std::to_string(gameHandler.score)},
                        {"Time", timeStr},
                        {"Mistakes", std::to_string(gameHandler.mistakes)},
                        {"Hints Used", std::to_string(gameHandler.hintsUsed)}
                };

                const size_t CHAR_NUM = 24;
                auto font = getFont("font");
                for (size_t i = 0; i < gameOverInfo.size(); i++)
                {
                        auto& info = gameOverInfo[i];
                        auto& title = info.first;
                        auto& value = info.second;

                        // Merge the title and value by dots to fill the space
                        std::string text = title
                                + std::string(CHAR_NUM - title.size() - value.size(), '.')
                                + value;

                        // Text
                        scene.addObject(std::make_shared<Text>(
                                "Game Over Text " + std::to_string(i),
                                X_POS + 22, Y_POS + 15 + 50 * i,
                                font.first, font.second,
                                text, 32, Colors::WHITE));
                }

        // Click to return box
                // Click-to-return function
                std::shared_ptr<Command> command = std::make_shared<Command>(
                        [&scene, &gui]()
                        {
                                createMainMenuScene(scene, gui);
                        });

                // Click-to-return rectangle
                scene.addClickableObject(createClickToContinue(command, window));
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

                auto microseconds = std::chrono::duration_cast<
                        std::chrono::microseconds>(time).count();
                if (microseconds < 1000000)
                {
                        std::stringstream ss;
                        ss << std::fixed << std::setprecision(3)
                                << std::setw(7) << std::setfill(' ')
                                << (microseconds / 1000.0);
                        timeStr += ss.str() + " ms";
                }
                else
                {
                        timeStr += " >1 s";
                        LOG_WARN("Execution time >1 s: {} ms", microseconds / 1000);
                }

                std::shared_ptr<Object> text = std::make_shared<Text>(
                        "Execution Time", bottomRight.x - 310, bottomRight.y - 30,
                        font.first, font.second, timeStr, 20,
                        Colors::WHITE);
                scene.addObject(text);
        }
} // namespace System