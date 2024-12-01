/*
Date: 10/11/2024

Game handler makes the connection between the GUI and the game logic.
*/

#include "../include/gameHandler.hpp"
#include "../include/generator.hpp"
#include "../include/macros.hpp"
#include "../include/grid.hpp"
#include "../include/solver.hpp"
#include <algorithm>
#include <chrono>
#include <random>

namespace Sudoku
{
// Class methods
        /*
        Constructor.

        @note Does not initialize the grid with a new game.
        */
        GameHandler::GameHandler()
        {
                LOG_TRACE("GameHandler::GameHandler() called");
        }

        /*
        Destructor.
        */
        GameHandler::~GameHandler()
        {
                LOG_TRACE("GameHandler::~GameHandler() called");
        }
// Game handler methods
        /*
        Generates a new game with the given difficulty.

        @param difficulty The difficulty of the game.
        */
        void GameHandler::newGame(Difficulty difficulty)
        {
                LOG_TRACE("GameHandler::newGame() called");

                // Set the difficulty
                this->difficulty = difficulty;

                // Generate a new grid
                generator.generate(grid);

                // Set the solved grid
                solved = grid;

                // Remove cells based on the difficulty
                size_t cells = static_cast<size_t>(difficulty);
                grid.setZero(grid.size() - cells);

                // Reset attributes
                score = 0;
                selectedCell = -1;
                selectedNumber = -1;
                hintsUsed = 0;
                mistakes = 0;
                notesMode = false;
                notes.reset();
                time.zero();
                cheat = false;

                #ifdef DEVELOPMENT
                // Log the current grid and solved grid for debugging
                Sudoku::Grid grid;
                getGrid(grid);
                LOG_DEBUG("Current grid:");
                grid.print();
                getGrid(grid, true);
                LOG_DEBUG("Solved grid:");
                grid.print();
                #endif // DEVELOPMENT
        }

        /*
        Checks if the user input is correct and sets the value in the grid if it is.

        @param index The index of the cell.
        @param value The value to check.

        @return True if the value is correct, false otherwise.
        */
        bool GameHandler::checkUserInput(int index, int value)
        {
                LOG_TRACE("GameHandler::checkUserInput() called");

                // Check if the value is correct
                bool isCorrect = value == solved.getCell(index);

                // If the value is correct, set it in the grid
                if (isCorrect)
                {
                        grid.setCell(index, value);

                        updateScore();
                }

                return isCorrect;
        }

        /*
        Solves the given number of cells in the grid.

        @param cells The number of cells to solve.

        @note If cells == 81, the entire grid is solved.
        */
        void GameHandler::solve(int cells)
        {
                LOG_TRACE("GameHandler::solve() called");

                // Find unsolved cells
                std::vector<size_t> unsolvedCells;
                unsolvedCells.reserve(grid.size());

                for (size_t i = 0; i < grid.size(); ++i)
                {
                        if (grid.getCell(i) == 0)
                        {
                                unsolvedCells.push_back(i);
                        }
                }

                if (cells >= unsolvedCells.size())
                {
                        grid = solved;
                }
                else
                {
                        std::shuffle(unsolvedCells.begin(), unsolvedCells.end(),
                                std::mt19937{std::random_device{}()});

                        for (size_t i = 0, index; i < cells; i++)
                        {
                                index = unsolvedCells[i];
                                grid.setCell(index, solved.getCell(index));
                        }
                }
        }
// Getters
        /*
        Gets the grid.

        @param grid The grid to store the values in.
        @param solved True if the solved grid is to be returned, false otherwise.
        */
        void GameHandler::getGrid(Grid& grid, bool solved) const
        {
                LOG_TRACE("GameHandler::getGrid() called");

                if (solved)
                {
                        grid = this->solved;
                }
                else
                {
                        grid = this->grid;
                }
        }
// Setters
        /*
        Sets the grid.

        @param grid The grid to set.
        */
        void GameHandler::setGrid(const Grid& grid)
        {
                LOG_TRACE("GameHandler::setGrid() called");

                this->grid = grid;
        }

// Checker
        /*
        Checks if the player has won the game.

        @return True if the player has won, false otherwise.
        */
        bool Sudoku::GameHandler::checkWin() const
        {
                LOG_TRACE("GameHandler::checkWin() called");

                return grid.isSolved() && mistakes < 3;
        }
// Game handler methods
        /*
        Updates the score based on the difficulty and time.

        @note This function is called after a correct user guess.
        */
        void GameHandler::updateScore()
        {
                LOG_TRACE("GameHandler::updateScore() called");

                // Get the time in seconds
                int seconds = time.count();

                float difficultyMultiplier = 0.0;

                // Calculate the difficulty multiplier
                switch (difficulty)
                {
                        case Difficulty::EASY:
                                difficultyMultiplier = 1;
                                break;
                        case Difficulty::MEDIUM:
                                difficultyMultiplier = 1.25;
                                break;
                        case Difficulty::HARD:
                                difficultyMultiplier = 1.5;
                                break;
                        case Difficulty::EXPERT:
                                difficultyMultiplier = 2;
                                break;
                        default:
                                LOG_ERROR("Invalid difficulty: {}",
                                        static_cast<int>(difficulty));
                                difficultyMultiplier = -1;
                                return;
                }

                // Calculate the score
                /*
                Formula:
                        score += 1800 - time (in seconds) + 100 * difficultyMultiplier - 20 * (hints + mistakes)

                        - 1800 or 30 minutes is used as the base score. We subtract current time in seconds from it
                                to encourage faster solving.
                        - 1000 is multiplied by the difficulty multiplier to reward harder difficulties.
                        - 200 is multiplied by the sum of hints and mistakes to penalize them. 200 is chosen as the
                                maximum value of hints is 3 and mistakes 2 (5 * 200 = 1000). This way we
                                prevent negative scores.
                        - The worst score possible is 0.
                */
                score += (1800 - seconds)                                       // Time incentive
                        + (1000 * difficultyMultiplier)                          // Difficulty reward
                        - (200 * (hintsUsed + mistakes));                        // Bad player penalty
        }

} // namespace Sudoku