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
#include <random>

namespace Sudoku
{
// Class methods
        /*
        Constructor. Initializes the grid, generator, and solver.

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

                // Generate a new grid
                generator.generate(grid);

                // Set the solved grid
                solved = grid;

                // Remove cells based on the difficulty
                int cells = static_cast<int>(difficulty);
                grid.setZero(81 - cells);
        }

        /*
        Checks if the user input is correct and sets the value in the grid if it is.

        @param row The row of the cell.
        @param col The column of the cell.
        @param value The value to check.

        @return True if the value is correct, false otherwise.
        */
        bool GameHandler::checkUserInput(int row, int col, int value)
        {
                LOG_TRACE("GameHandler::checkUserInput() called");

                // Check if the value is correct
                bool isCorrect = grid.isValidValue(row, col, value);

                // If the value is correct, set it in the grid
                if (isCorrect)
                {
                        grid.setCell(row, col, value);
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
                std::vector<int> unsolvedCells;
                for (int i = 0; i < 81; i++)
                {
                        if (grid.getCell(i) == 0)
                        {
                                unsolvedCells.push_back(i);
                        }
                }

                // Solve the grid if the number of cells is invalid
                // or the entire grid is to be solved
                if (cells == 81 || cells >= static_cast<int>(
                        unsolvedCells.size()) || cells <= 0)
                {
                        grid = solved;
                        return;
                }

                // Shuffle the unsolved cells
                std::shuffle(unsolvedCells.begin(), unsolvedCells.end(),
                        std::mt19937(std::random_device()()));

                // Solve the desired number of cells
                int cell;
                for (int i = 0; i < cells; i++)
                {
                        cell = unsolvedCells[i];
                        grid.setCell(cell, solved.getCell(cell));
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
}