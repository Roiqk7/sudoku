/*
Date: 15/11/2024

This file contains pre-made scenes for the GUI.
*/

#include "colors.hpp"
#include "command.hpp"
#include "gameHandler.hpp"
#include "grid.hpp"
#include "gui.hpp"
#include "guiHelper.hpp"
#include "macros.hpp"
#include "object.hpp"
#include "scene.hpp"
#include "scenes.hpp"
#include "soundEffect.hpp"
#include <array>
#include <bitset>
#include <chrono>
#include <cmath>
#include <filesystem>
#include <functional>
#include <iomanip>
#include <memory>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <string>
#include <thread>
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
                        wi.size.x/5 + 120, wi.size.y/8, 10, Colors::BLACK, Colors::WHITE, command,
                        "font", wi.center.y / 5, "New Game", Colors::BLACK);
                scene.addObject(NGButton.frame);
                scene.addClickableObject(NGButton.clickable);
                scene.addObject(NGButton.background);
                scene.addObject(NGButton.text);
        // Credits Button
                // Credits clickable black rectangle
                // Credits function
                std::shared_ptr<Command> command2 = std::make_shared<Command>(
                        [&scene, &gui]()
                        {
                                createCreditsScene(scene, gui);
                        });
                auto creditsButton = createButton("Credits", wi.center.x - 210, wi.center.y + 20,
                        wi.size.x/5 + 120, wi.size.y/8, 10, Colors::BLACK, Colors::WHITE, command2,
                        "font", wi.center.y / 5, "Credits", Colors::BLACK);
                scene.addObject(creditsButton.frame);
                scene.addClickableObject(creditsButton.clickable);
                scene.addObject(creditsButton.background);
                scene.addObject(creditsButton.text);
        // Exit Button
                // Exit clickable black rectangle
                // Exit function
                std::shared_ptr<Command> command3 = std::make_shared<Command>(
                        [&window]()
                        {
                                window.close();
                        });

                auto exitButton = createButton("Exit", wi.center.x - 210, wi.center.y + 140,
                        wi.size.x/5 + 120, wi.size.y/8, 10, Colors::BLACK, Colors::WHITE, command3,
                        "font", wi.center.y / 5, "Exit", Colors::BLACK);
                scene.addObject(exitButton.frame);
                scene.addClickableObject(exitButton.clickable);
                scene.addObject(exitButton.background);
                scene.addObject(exitButton.text);
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
                        std::make_shared<Command>(command),
                        "font", wi.center.y / 5, diffName, Colors::BLACK);
                scene.addObject(button.frame);
                scene.addClickableObject(button.clickable);
                scene.addObject(button.background);
                scene.addObject(button.text);
        }

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
                // TODO: Add more "function wide" variables to make everything more connected
                // TODO: Add a header with all the important variables (e.g., highlight color)
                // TODO: Create a separate function for the highlite, numbers and grid lines
                // etc. to make editing easier

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

                // Create the main click function
                std::shared_ptr<Command> boardClickCommand = std::make_shared<Command>(
                        [&scene, &gui, GRID_SIZE, GRID_X, GRID_Y]()
                        {
                                gameSceneMainGridClick(scene, gui, GRID_SIZE, GRID_X, GRID_Y);
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

                /*
                Add highlight effect (we do this before creating the grid lines
                to make sure the highlight is bellow the grid lines)

                We will highlight all cells with the clicked number and the row,
                column and box of selected cell
                */
                if (grid.checkCellIndex(gameHandler.selectedCell))
                {
                        // Row and column are in the range [0, 8]
                        int row = gameHandler.selectedCell / 9;
                        int col = gameHandler.selectedCell % 9;

                        if (!grid.checkIndex(row) || !grid.checkIndex(col))
                        {
                                // This error is severe as this code should get executed only if
                                // the selected cell is valid (i.e., in the range [0, 80]) and
                                // that should imply that the row and column are also valid.
                                LOG_ERROR("Invalid selected cell: {} [{}x{}]. Grid index calculations are likely wrong.",
                                        gameHandler.selectedCell, row, col);
                                return;
                        }

                        // First, we highlight the row, column and box of the selected cell
                        // Highlight the row
                        scene.addObject(std::make_shared<Rectangle>(
                                "Highlight Row",
                                GRID_X, GRID_Y + (GRID_SIZE / 9) * row,
                                GRID_SIZE, GRID_SIZE / 9, Colors::ORANGE));

                        // Highlight the column
                        scene.addObject(std::make_shared<Rectangle>(
                                "Highlight Column",
                                GRID_X + (GRID_SIZE / 9) * col, GRID_Y,
                                GRID_SIZE / 9, GRID_SIZE, Colors::ORANGE));

                        // Highlight the box
                        int boxRow = row / 3;
                        int boxCol = col / 3;
                        // We add this as the highlight box is weird on the end edges
                        int xOffset = boxRow == 2 ? 5 : 0;
                        int yOffset = boxCol == 2 ? 5 : 0;
                        scene.addObject(std::make_shared<Rectangle>(
                                "Highlight Box",
                                GRID_X + (GRID_SIZE / 3) * boxCol - boxCol,
                                GRID_Y + (GRID_SIZE / 3) * boxRow - boxRow,
                                GRID_SIZE / 3 + yOffset, GRID_SIZE / 3 + xOffset,
                                Colors::ORANGE));

                        // Now highlight cells with the clicked number
                        int clickedNumber = grid.getCell(gameHandler.selectedCell / 9, gameHandler.selectedCell % 9);
                        if (clickedNumber != 0)
                        {
                                for (int row = 0; row < 9; row++)
                                {
                                        for (int col = 0; col < 9; col++)
                                        {
                                                if (grid.getCell(row, col) == clickedNumber)
                                                {
                                                        scene.addObject(std::make_shared<Rectangle>(
                                                                "Highlight Number",
                                                                GRID_X + (GRID_SIZE / 9) * col, GRID_Y + (GRID_SIZE / 9) * row,
                                                                GRID_SIZE / 9, GRID_SIZE / 9, Colors::RED));
                                                }
                                        }
                                }
                        }
                }

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
                        int x, y, num;
                        for (int col = 0; col < 9; col++)
                        {
                                num = grid.getCell(row, col);

                                x = GRID_X + 12 + col * NUM_OFFSET - col * (NUM_OFFSET / 20);
                                y = GRID_Y - 8 + row * NUM_OFFSET - row * (NUM_OFFSET / 20);

                                // Non-empty cell
                                if (num != 0)
                                {
                                        // Board number
                                        std::string numStr = std::to_string(num);
                                        std::shared_ptr<Object> number = std::make_shared<Text>(
                                                "numStr",
                                                x, y,
                                                font.first, font.second,
                                                numStr, NUM_SIZE, Colors::WHITE);
                                        scene.addObject(number);
                                }
                                // Empty cell
                                else
                                {
                                        // We correct x and y to align with the cell
                                        x -= 10;
                                        y += 5;

                                        // Check for notes
                                        for (int val = 0; val < 9; val++)
                                        {
                                                if (gameHandler.notes[grid.convertIndex(row, col) * 9 + val])
                                                {
                                                        // Note number
                                                        std::string noteStr = std::to_string(val + 1);
                                                        scene.addObject(std::make_shared<Text>(
                                                                "noteStr" + noteStr,
                                                                x + val % 3 * 25, y + val / 3 * 22,
                                                                font.first, font.second,
                                                                noteStr, NUM_SIZE / 3, Colors::WHITE));
                                                }
                                        }
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
                        case Sudoku::Difficulty::CHEAT:
                                difficultyStr += "Invalid (Cheat)";
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
                        GRID_X + GRID_SIZE + FRAME_MARGIN + 20, GRID_Y,
                        font.first, font.second,
                        "Score: " + std::to_string(gameHandler.score), 40,
                        Colors::WHITE);
                scene.addObject(scoreText);\
        // Mistakes counter
                // Mistakes text
                std::string mistakesStr = std::to_string(gameHandler.mistakes);
                sf::Color mistakesColor = gameHandler.mistakes == 2 ? Colors::RED : Colors::WHITE;
                std::shared_ptr<Object> mistakesText = std::make_shared<Text>(
                        "Mistakes Text",
                        GRID_X + GRID_SIZE + FRAME_MARGIN + 20, GRID_Y + 60,
                        font.first, font.second,
                        "Mistakes: " + mistakesStr, 40,
                        Colors::WHITE);
                scene.addObject(mistakesText);

        // Hints text
                std::shared_ptr<Object> hintsText = std::make_shared<Text>(
                        "Hints Text",
                        GRID_X + GRID_SIZE + FRAME_MARGIN + 20, GRID_Y - FRAME_MARGIN + 140,
                        font.first, font.second,
                        "Hints: " + std::to_string(gameHandler.hintsUsed) + "/3", 40,
                        Colors::WHITE);
                scene.addObject(hintsText);
        // Solve Button
                // Solve clickable rectangle
                // Solve function
                std::shared_ptr<Command> solveCommand = std::make_shared<Command>(
                        [&scene, &gui]()
                        {
                                auto& gameHandler = gui.getGameHandler();
                                gameHandler.difficulty = Sudoku::Difficulty::CHEAT;
                                gameHandler.cheat = true;
                                auto& soundEffect = gui.getSoundEffect();
                                soundEffect.playSound("solve");

                                int iterations = 0;
                                while(!gameHandler.checkWin())
                                {
                                        // Iterate
                                        gameHandler.solve(1);
                                        gameHandler.hintsUsed++;
                                        gameHandler.score *= 0.9;

                                        // Render
                                        createGameScene(scene, gui);
                                        gui.render();

                                        // Sleep
                                        auto sleepTime = std::chrono::milliseconds(1000 / iterations + 1);
                                        std::this_thread::sleep_for(sleepTime);
                                }

                                // Let the user see the solved board
                                // TODO: Implement a better way to show the solved board
                                std::this_thread::sleep_for(std::chrono::seconds(2));

                                createGameOverScene(scene, gui, false);
                        });
                sf::Color solveColor = gameHandler.cheat ? Colors::SHADOW
                        : Colors::WHITE;
                auto solveButton = createButton("Solve",
                        wi.topLeft.x + 60, GRID_Y,
                        260, 100, 10, Colors::BLACK, solveColor, solveCommand,
                        "font", 80, "Solve", Colors::BLACK);
                scene.addObject(solveButton.frame);
                scene.addClickableObject(solveButton.clickable);
                scene.addObject(solveButton.background);
                scene.addObject(solveButton.text);
        // Hint Button
                // Hint clickable rectangle
                // Hint function
                std::shared_ptr<Command> hintCommand = std::make_shared<Command>(
                        [&scene, &gui]()
                        {
                                auto& gameHandler = gui.getGameHandler();

                                if (gameHandler.hintsUsed < 3)
                                {
                                        // Play sound
                                        auto& soundEffect = gui.getSoundEffect();
                                        soundEffect.playSound("hint");

                                        // Solve one cell
                                        gameHandler.solve(1);
                                        gameHandler.hintsUsed++;
                                        createGameScene(scene, gui);
                                }
                        });
                sf::Color hintsColor = gameHandler.hintsUsed == 0 ? Colors::WHITE
                        : gameHandler.hintsUsed == 1 ? Colors::GREEN
                        : gameHandler.hintsUsed == 2 ? Colors::BLUE
                        : Colors::SHADOW;
                auto hintButton = createButton("Hint",
                        wi.topLeft.x + 60, GRID_Y + 120,
                        260, 100, 10, Colors::BLACK, hintsColor, hintCommand,
                        "font", 80, "Hint", Colors::BLACK);
                scene.addObject(hintButton.frame);
                scene.addClickableObject(hintButton.clickable);
                scene.addObject(hintButton.background);
                scene.addObject(hintButton.text);
        // Notes switch button
                // Notes switch clickable rectangle
                // Notes switch function
                std::shared_ptr<Command> notesSwitchCommand = std::make_shared<Command>(
                        [&scene, &gui]()
                        {
                                auto& gameHandler = gui.getGameHandler();
                                gameHandler.notesMode = !gameHandler.notesMode;
                                createGameScene(scene, gui);
                        });

                sf::Color notesSwitchColor = gameHandler.notesMode ? Colors::GREEN : Colors::WHITE;
                auto& notesSwitchButton = createButton("Notes Switch",
                        wi.topLeft.x + 60, GRID_Y + 240,
                        260, 100, 10, Colors::BLACK, notesSwitchColor, notesSwitchCommand);
                scene.addObject(notesSwitchButton.frame);
                scene.addClickableObject(notesSwitchButton.clickable);
                scene.addObject(notesSwitchButton.background);

                // Notes switch text
                scene.addObject(std::make_shared<Text>(
                        "Notes Switch Text", wi.topLeft.x + 70, GRID_Y + 240,
                        font.first, font.second, "Notes", 80, Colors::BLACK));
        // Number Panel
                // Constants
                const int NUM_PANEL_SIZE = 300;
                const int NUM_PANEL_X = GRID_X + GRID_SIZE + 40;
                const int NUM_PANEL_Y = wi.center.y - 110;
                // Number panel click function
                std::shared_ptr<Command> numberPanelClickCommand = std::make_shared<Command>(
                        [&scene, &gui, NUM_PANEL_SIZE, NUM_PANEL_X, NUM_PANEL_Y]()
                        {
                                gameSceneNumberPanelClick(scene, gui,
                                        NUM_PANEL_SIZE, NUM_PANEL_X, NUM_PANEL_Y);
                        });
                auto& numberPanel = createButton("Number Panel",
                        GRID_X + GRID_SIZE + 30, wi.center.y - 120,
                        NUM_PANEL_SIZE + 20, NUM_PANEL_SIZE + 20, 10,
                        Colors::WHITE, Colors::NAVAJO_WHITE,
                        numberPanelClickCommand);
                scene.addObject(numberPanel.frame);
                scene.addClickableObject(numberPanel.clickable);
                scene.addObject(numberPanel.background);

                // Number panel highlight
                if (gameHandler.selectedNumber > 0 and gameHandler.selectedNumber < 10)
                {
                        int row = (gameHandler.selectedNumber - 1) / 3;
                        int col = (gameHandler.selectedNumber - 1) % 3;

                        scene.addObject(std::make_shared<Rectangle>(
                                "Number Panel Highlight",
                                NUM_PANEL_X + col * (NUM_PANEL_SIZE / 3),
                                NUM_PANEL_Y + row * (NUM_PANEL_SIZE / 3),
                                NUM_PANEL_SIZE / 3, NUM_PANEL_SIZE / 3,
                                Colors::ORANGE));
                }

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
        // Catch-all click rect
                // Used as deselect button
                // Catch-all click function
                std::shared_ptr<Command> catchAllCommand = std::make_shared<Command>(
                        [&scene, &gui]()
                        {
                                auto& gameHandler = gui.getGameHandler();
                                gameHandler.selectedCell = -1;
                                gameHandler.selectedNumber = -1;
                                createGameScene(scene, gui);
                        });
                scene.addClickableObject(std::make_shared<Rectangle>(
                        "Catch All", wi.topLeft.x, wi.topLeft.y,
                        wi.size.x, wi.size.y, Colors::TRANSPARENT, catchAllCommand));
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
                        Colors::BLACK, Colors::WHITE, command,
                        "font", wi.center.y / 5, "Resume", Colors::BLACK);
                scene.addObject(resumeButton.frame);
                scene.addClickableObject(resumeButton.clickable);
                scene.addObject(resumeButton.background);
                scene.addObject(resumeButton.text);
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
                        Colors::BLACK, Colors::WHITE, command2,
                        "font", wi.center.y / 5, "Help", Colors::BLACK);
                scene.addObject(helpButton.frame);
                scene.addClickableObject(helpButton.clickable);
                scene.addObject(helpButton.background);
                scene.addObject(helpButton.text);
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
                        Colors::BLACK, Colors::WHITE, command3,
                        "font", wi.center.y / 5, "Exit", Colors::BLACK);
                scene.addObject(exitButton.frame);
                scene.addClickableObject(exitButton.clickable);
                scene.addObject(exitButton.background);
                scene.addObject(exitButton.text);
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

                // Sound effect
                auto& soundEffect = gui.getSoundEffect();
                soundEffect.playSound(win ? "won" : "lost");

                // Sudoku title
                scene.addObject(getTitle(window));

                const int X_POS = wi.center.x - 250;
                const int Y_POS = wi.topLeft.y + 260;
                const int X_SIZE = wi.topLeft.x + 500;
                const int Y_SIZE = wi.topLeft.y + 320;

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

        // Exit Button
                // Exit clickable black rectangle
                // Exit function
                std::shared_ptr<Command> command = std::make_shared<Command>(
                        [&scene, &gui]()
                        {
                                createMainMenuScene(scene, gui);
                        });

                auto& exitButton = createButton("Exit",
                        wi.center.x - 210, wi.center.y + 220,
                        wi.size.x/5 + 120, wi.size.y/8, 10,
                        Colors::BLACK, Colors::WHITE, command,
                        "font", wi.center.y / 5, "Exit", Colors::BLACK);
                scene.addObject(exitButton.frame);
                scene.addClickableObject(exitButton.clickable);
                scene.addObject(exitButton.background);
                scene.addObject(exitButton.text);
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