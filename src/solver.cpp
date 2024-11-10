/*
Date: 09/11/2024

Solver is class which given a sudoku grid, solves it using backtracking. I tried to implement
stochastic approach using this paper [https://arxiv.org/pdf/0805.0697, 4.4] but it was too complex
and way too slow. So I decided to implement backtracking instead.
*/

#include "../include/globals.hpp"
#include "../include/grid.hpp"
#include "../include/solver.hpp"
#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

namespace Sudoku
{
// Class methods
        /*
        Constructor for the Solver class.
        */
        Solver::Solver()
        {
                LOG_TRACE("Solver::Solver() called");
        }

        /*
        Destructor for the Solver class.
        */
        Solver::~Solver()
        {
                LOG_TRACE("Solver::~Solver() called");
        }
// Solver methods
        /*
        Solves the sudoku grid using backtracking.

        @param grid The grid to solve.

        @note Missing numbers are represented by zeros and the fixed numbers
        are assumed to be correct.
        */
        void Solver::solve(Grid& grid)
        {
                LOG_TRACE("Solver::solve() called");

                if (backtrack(grid, 0, 0))
                {
                        LOG_INFO("Sudoku grid solved successfully");
                }
                else
                {
                        LOG_ERROR("Failed to solve sudoku grid");
                }
        }

        /*
        Recursive function to solve the sudoku grid using backtracking.

        @param grid The grid to solve.
        @param row The row of the cell to solve.
        @param col The column of the cell to solve.

        @return True if the grid is solved, false otherwise.
        */
        bool Solver::backtrack(Grid& grid, int row, int col)
        {
                LOG_TRACE("Solver::backtrack() called");

                // If we have reached the end of the grid, return true
                if (row == 9)
                {
                        return true;
                }

                // Move to the next cell if the current cell is not empty
                if (grid.getCell(row, col) != 0)
                {
                        return backtrack(grid, row + (col + 1) / 9, (col + 1) % 9);
                }

                // Try all numbers from 1 to 9
                for (int num = 1; num <= 9; num++)
                {
                        if (grid.isValidValue(row, col, num))
                        {
                                grid.setCell(row, col, num);

                                if (backtrack(grid, row + (col + 1) / 9, (col + 1) % 9))
                                {
                                        return true;
                                }

                                grid.setCell(row, col, 0);
                        }
                }

                return false;
        }
}