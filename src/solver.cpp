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

                // If the cell is not empty, move to the next cell
                if (grid.getCell(row, col) != 0)
                {
                        if (col == 8)
                        {
                                return backtrack(grid, row + 1, 0);
                        }
                        else
                        {
                                return backtrack(grid, row, col + 1);
                        }
                }

                // Generate possibilities for the cell
                std::vector<int> possibilities;
                generatePossibilities(grid, row, col, possibilities);

                // Try all possibilities for the cell
                for (int i = 0; i < possibilities.size(); i++)
                {
                        int value = possibilities[i];
                        grid.setCell(row, col, value);

                        if (col == 8)
                        {
                                if (backtrack(grid, row + 1, 0))
                                {
                                        return true;
                                }
                        }
                        else
                        {
                                if (backtrack(grid, row, col + 1))
                                {
                                        return true;
                                }
                        }

                        grid.setCell(row, col, 0);
                }

                return false;
        }
// Utility methods
        /*
        Generates the possibilities for each cell in the grid.

        @param grid The grid to generate possibilities for.
        @param possibilities The array of possibilities for each cell.
        */
        void Solver::generatePossibilities(Grid& grid, int row, int col,
                std::vector<int>& possibilities)
        {
                LOG_TRACE("Solver::generatePossibilities() called");

                possibilities.clear();
                for (int i = 1; i <= 9; i++)
                {
                        if (grid.isValidValue(row, col, i))
                        {
                                possibilities.push_back(i);
                        }
                }
        }
}