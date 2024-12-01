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
                CHEAT = 81,
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
                bool checkUserInput(int index, int value);
                void solve(int cells);
        // Getters
                void getGrid(Grid& grid, bool solved = false) const;
        // Setters
                void setGrid(const Grid& grid);
        // Checker
                bool checkWin() const;
        private: // Methods
        // Game handler methods
                void updateScore();
        public: // Variables
                int score = 0;                                                  // The score of the player
                int selectedCell = -1;                                          // The cell selected by the player [0, 80]
                int selectedNumber = 0;                                         // The number selected by the player [1, 9]
                Difficulty difficulty = Difficulty::NONE;                       // The difficulty of the game
                int mistakes = 0;                                               // Number of mistakes made (max 3)
                bool notesMode = false;                                         // If notes mode is enabled
                std::bitset<81*9> notes;                                        // Notes for each cell (1 if note is given)
                int hintsUsed = 0;                                              // Number of hints used
                std::chrono::seconds time;                                      // Time taken to solve the grid (in seconds)
                bool cheat = false;                                             // If the player is cheating
        private: // Variables
                Grid grid;                                                      // What the player sees
                Grid solved;                                                    // The solved grid
                Generator generator;                                            // Generates a new sudoku grid
                Solver solver;                                                  // Solves the sudoku grid
        };
}

#endif // !GAME_HANDLER_HPP