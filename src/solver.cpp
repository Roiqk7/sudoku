/*
Date: 09/11/2024

Solver is class which given a sudoku grid, solves it using backtracking.
*/

#include "macros.hpp"
#include "grid.hpp"
#include "solver.hpp"
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

                bool result = backtrack(grid, 0, zeroCount);

                const std::string resultStr = result ? "Successfully solved"
                        : "Failed to solve";

                LOG_DEBUG("Solver::solve() result: {} the puzzle", resultStr);

                return result;
        }

        /*
        Recursive function to solve the sudoku grid using backtracking.

        @param grid The grid to solve.
        @param index The index of the cell to solve.

        @return True if the grid is solved, false otherwise.
        */
        bool Solver::backtrack(Grid& grid, size_t index, int zeroCount)
        {
                LOG_TRACE("Solver::backtrack() called");

                // If there are no zeros left, the grid is solved
                if (zeroCount <= 0 || index >= grid.size())
                {
                        return true;
                }

                // Find next empty cell
                while (grid.getCell(index) != 0 && index < grid.size())
                {
                        index++;
                }

                // Try all numbers from 1 to 9
                for (int num = 1; num <= 9; num++)
                {
                        if (grid.isValidValueToSet(index, num))
                        {
                                grid.setCell(index, num);

                                if (backtrack(grid, index + 1, zeroCount - 1))
                                {
                                        return true;
                                }

                                grid.setCell(index, 0);
                        }
                }

                return false;
        }
}