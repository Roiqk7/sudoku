/*
Date: 10/11/2024

Game handler makes the connection between the GUI and the game logic.
*/

#ifndef GAME_HANDLER_HPP
#define GAME_HANDLER_HPP

#include "generator.hpp"
#include "grid.hpp"
#include "solver.hpp"
#include <bitset>
#include <chrono>

namespace Sudoku
{
        /*
        Number of given based on difficulty:
        Easy: 34-38
        Medium: 29-33
        Hard: 24-28
        Expert: 19-23

        @note NONE is used as a default value.
        */
        enum class Difficulty
        {
                NONE = 0,
                EASY = 36,
                MEDIUM = 31,
                HARD = 26,
                EXPERT = 21
        };

        class GameHandler
        {
        public: // Methods
        // Class methods
                GameHandler();
                ~GameHandler();
        // Game handler methods
                void newGame(Difficulty difficulty);
                bool checkUserInput(int row, int col, int value);
                void solve(int cells);
        // Getters
                void getGrid(Grid& grid, bool solved = false) const;
        // Setters
                void setGrid(const Grid& grid);
        public: // Variables
                int mistakes = 0;                                               // Number of mistakes made (max 3)
                std::bitset<81*9> notes;                                        // Notes for each cell
                std::chrono::seconds time;                                      // Time taken to solve the grid (in seconds)
        private: // Variables
                Grid grid;                                                      // What the player sees
                Grid solved;                                                    // The solved grid
                Generator generator;                                            // Generates a new sudoku grid
                Solver solver;                                                  // Solves the sudoku grid
        };
}

#endif // !GAME_HANDLER_HPP