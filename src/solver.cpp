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

        @return True if the grid is solved, false otherwise.

        @note Missing numbers are represented by zeros and the fixed numbers
        are assumed to be correct.
        */
        bool Solver::solve(Grid& grid)
        {
                LOG_TRACE("Solver::solve() called");

                int zeroCount = grid.count(0);

                bool result = backtrack(grid, 0, 0, zeroCount);

                #ifdef DEVELOPMENT
                LOG_DEBUG("Solver::solve() result: {}", result);
                LOG_DEBUG("Solver::solve() grid:");
                grid.print();
                LOG_DEBUG("Solver::solve() end of grid");
                #endif // DEVELOPMENT

                return result;
        }

        /*
        Recursive function to solve the sudoku grid using backtracking.

        @param grid The grid to solve.
        @param row The row of the cell to solve.
        @param col The column of the cell to solve.

        @return True if the grid is solved, false otherwise.
        */
        bool Solver::backtrack(Grid& grid, int row, int col, int zeroCount)
        {
                LOG_TRACE("Solver::backtrack() called");

                // If there are no zeros left, the grid is solved
                if (zeroCount == 0)
                {
                        return true;
                }

                // Find next empty cell
                while (grid.getCell(row, col) != 0)
                {
                        col = (col + 1) % 9;
                        row += (col == 0);
                }

                // Try all numbers from 1 to 9
                for (int num = 1; num <= 9; num++)
                {
                        if (grid.isValidValue(row, col, num))
                        {
                                grid.setCell(row, col, num);

                                if (backtrack(grid, row + (col + 1) / 9, (col + 1) % 9, zeroCount - 1))
                                {
                                        return true;
                                }

                                grid.setCell(row, col, 0);
                        }
                }

                return false;
        }
}