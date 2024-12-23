/*
Date: 15/11/2024

This file contains helper functions for the GUI.
*/

#include "grid.hpp"
#include "gui.hpp"
#include "guiHelper.hpp"
#include "scenes.hpp"
#include "macros.hpp"
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
                const std::shared_ptr<Command>& command,
                const std::shared_ptr<Object>& text)
                : frame(frame), clickable(clickable),
                background(background), command(command),
                text(text)
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
        @param fontName Name of the font.
        @param fontSize Size of the font.
        @param text Text of the button.
        @param textColor Color of the text.

        @return Pointer to the button.

        @note The button is created with a frame, background, and clickable object.
        */
        Button& createButton(const std::string& name,
                        const int x, const int y,
                        const int width, const int height,
                        const int margin,
                        const sf::Color frameColor,
                        const sf::Color backgroundColor,
                        const std::shared_ptr<Command>& command,
                        const std::string& fontName, const int fontSize,
                        const std::string& textStr, const sf::Color textColor)
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
                /*
                The offset calculation is a bit of a magic. The way it works is that the
                width : height ratio of the text is 0.625. (meaning that the width of the
                character is 0.625 times the height of the character and height == fontSize).

                Thus we get the total width of the text by multiplying the number of characters
                in the text by the width of the character. We then subtract from the total width
                and divide by 2 to center the text. The margin is added to the x position to
                center the text within the button background. The 0.625 is a magic number and
                is not precise but works well enough for the purpose of this program.
                */
                int offset = (width - (textStr.size() * (fontSize * 0.625))) / 2 + margin;
                auto text = textStr != "" ? std::make_shared<Text>(
                        name + " Text", x + offset, y,
                        getFont(fontName).first, getFont(fontName).second,
                        textStr, fontSize, textColor)
                        : nullptr;

                return *new Button(frame, clickable, background, command, text);
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
                        case Sudoku::Difficulty::CHEAT:
                                return "Invalid";
                        default:
                                return "None";
                }
        }
// Click functions helper
        /*
        Determines if the user input should be considered valid.

        @param gridValueAtSelectedCell Value at the selected cell. [0, 9]
        @param selectedCell Selected cell. [0, 80]
        @param selectedNumber Selected number. [1, 9]
        */
        bool isValidGameSceneMainGridUserInput(
                const int gridValueAtSelectedCell,
                const int selectedCell, const int selectedNumber)
        {
                LOG_TRACE("isValidGameSceneMainGridUserInput() called.");

                /*
                The input is valid only if user selected an empty cell and
                selected a number. The selectedCell argument is redundant
                but is kept for clarity.
                */
                return gridValueAtSelectedCell == 0
                        and 1 <= selectedNumber and selectedNumber <= 9
                        and 0 <= selectedCell and selectedCell <= 80;
        }

        /*
        Handles valid user input in the main grid of the game scene.

        @param scene Scene to handle the input in.
        @param gui GUI to handle the input in.
        @param selectedCell Selected cell. [0, 80]
        @param selectedNumber Selected number. [1, 9]

        @note This function holds all the logic for valid user input in the main grid.
        */
        void gameSceneMainGridUserInputHandle(Scene& scene, GUI& gui,
                const int selectedCell, const int selectedNumber)
        {
                LOG_TRACE("gameSceneMainGridUserInputHandle() called.");

                auto& gameHandler = gui.getGameHandler();
                auto& soundEffect = gui.getSoundEffect();
                bool correctGuess = gameHandler.checkUserInput(selectedCell, selectedNumber);

                // Either add a note or a guess
                // Note
                if (gameHandler.notesMode)
                {
                        /*
                        The index calculations is as follows because the notes array
                        stores for each cell 9 buckets for each number which could be
                        a note. The index is calculated by multiplying the cell index
                        by 9 and adding the selected number - 1 to get the correct
                        bucket.
                        */
                        int index = selectedCell * 9 + selectedNumber - 1;
                        bool value = gameHandler.notes.test(index);

                        // Add or remove note
                        gameHandler.notes = gameHandler.notes.set(index, !value);
                }
                // Correct guess
                else if (correctGuess)
                {
                        soundEffect.playSound("correct");

                        // Check win condition
                        if (gameHandler.checkWin())
                        {
                                return createGameOverScene(scene, gui, true);
                        }
                }
                // Incorrect guess
                else if (!correctGuess)
                {
                        soundEffect.playSound("mistake");

                        if (++gameHandler.mistakes >= 3)
                        {
                                return createGameOverScene(scene, gui, false);
                        }
                }
                #ifdef DEVELOPMENT
                else
                {
                        LOG_WARN("Invalid main grid click handling. This log message should not appear.");
                }
                #endif // DEVELOPMENT

                createGameScene(scene, gui);
        }

        /*
        Handles what to do when the user interacts with the sudoku grid.

        @param scene Scene to handle the input in.
        @param gui GUI to handle the input in.
        @param selectedCell Selected cell. [0, 80]
        @param selectedCellValue Selected cell value. [0, 9]
        @param selectedNumber Selected number. [1, 9]

        @note This function is used when the user clicked either on the main grid
        or the number panel.
        */
        void gameSceneGridInputHandle(Scene& scene, GUI& gui,
                const int selectedCell, const int selectedCellValue, const int selectedNumber)
        {
                LOG_TRACE("gameSceneNumberPanelUserInputHandle() called.");

                auto& gameHandler = gui.getGameHandler();

                // Check if user intended to insert a number
                if (isValidGameSceneMainGridUserInput(
                        gameHandler.selectedCellValue,
                        gameHandler.selectedCell, gameHandler.selectedNumber))
                {
                        gameSceneMainGridUserInputHandle(scene, gui,
                                gameHandler.selectedCell, gameHandler.selectedNumber);
                }
                else
                {
                        createGameScene(scene, gui);
                }
        }

// Click functions
        /*
        The main grid click function for the game scene.

        @param scene Scene to handle the click in.
        @param gui GUI to handle the click in.
        @param gridSize Size of the grid.
        @param gridX X position of the grid.
        @param gridY Y position of the grid
        */
        void gameSceneMainGridClick(Scene& scene, GUI& gui, const int gridSize,
                const int gridX, const int gridY)
        {
                LOG_TRACE("gameSceneMainGridClick() called.");

                // Get the event
                sf::Event event = gui.getEvent();
                // Ignore if not a mouse click
                // Note: Should not happen
                if (event.type != sf::Event::MouseButtonPressed)
                {
                        // This function should only be called on mouse click
                        LOG_WARN("Ignoring non-mouse click event. This log message should not appear.");
                        return;
                }

                // Find the selected cell
                auto& window = gui.getWindow();
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                // Note: These numbers should be in the range [0, 8]
                int row = (mousePos.y - gridY) / (gridSize / 9);
                int col = (mousePos.x - gridX) / (gridSize / 9);

                // Get the grid
                auto& gameHandler = gui.getGameHandler();
                Sudoku::Grid grid;
                gameHandler.getGrid(grid);
                // Validate the row and column
                // Note: row and col should be in the range [0, 8]
                if (!grid.checkCellIndex(row, col))
                {
                        LOG_WARN("Invalid row x col: {} x {} (index: {}. This log message should not appear.",
                                row, col, grid.convertIndex(row, col));
                        return;
                }

                // Now we can be sure the input is valid

                // Set the selected cell and value
                gameHandler.selectedCell = grid.convertIndex(row, col);
                gameHandler.selectedCellValue = grid.getCell(row, col);

                // Determine what the user wants to do
                gameSceneGridInputHandle(scene, gui,
                        gameHandler.selectedCell, gameHandler.selectedCellValue,
                        gameHandler.selectedNumber);
        }

        /*
        The number panel click function for the game scene.

        @param scene Scene to handle the click in.
        @param gui GUI to handle the click in.
        @param numberPanelSize Size of the number panel.
        @param numberPanelX X position of the number panel.
        @param numberPanelY Y position of the number panel.
        */
        void gameSceneNumberPanelClick(Scene& scene, GUI& gui,
                const int numberPanelSize,
                const int numberPanelX, const int numberPanelY)
        {
                LOG_TRACE("gameSceneNumberPanelClick() called.");

                sf::Event event = gui.getEvent();

                // Ignore if not a mouse click
                // Should not happen
                if (event.type != sf::Event::MouseButtonPressed)
                {
                        LOG_WARN("Ignoring non-mouse click event. This log message should not appear.");
                        return;
                }

                // Find the selected number
                auto& window = gui.getWindow();
                auto& gameHandler = gui.getGameHandler();
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                // Note: row and col should be in the range [0, 2]
                int row = (mousePos.y - numberPanelY) / (numberPanelSize / 3);
                int col = (mousePos.x - numberPanelX) / (numberPanelSize / 3);
                if (row < 0 or row > 2 or col < 0 or col > 2)
                {
                        LOG_WARN("Invalid row x col: {} x {}. This log message should not appear.",
                                row, col);
                        return;
                }

                /*
                Layout:
                        1 2 3
                        4 5 6
                        7 8 9
                */
                // Get the number
                int num = row * 3 + col + 1;

                // Select/deselect the number
                gameHandler.selectedNumber = gameHandler.selectedNumber == num ? -1 : num;

                // Determine what the user wants to do
                gameSceneGridInputHandle(scene, gui,
                        gameHandler.selectedCell, gameHandler.selectedCellValue,
                        gameHandler.selectedNumber);
        }

} // namespace System