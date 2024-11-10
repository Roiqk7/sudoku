/*
Date: 09/11/2024

Solver is class which given a sudoku grid, solves it Stochastic search / optimization methods.
*/

#ifndef SUDOKU_SOLVER_HPP
#define SUDOKU_SOLVER_HPP

#include "grid.hpp"
#include <vector>

namespace Sudoku
{
        class Solver
        {
        public: // Methods
        // Class methods
                Solver();
                ~Solver();
        // Solver methods
                bool solve(Grid& grid);
                bool backtrack(Grid& grid, int row, int col, int zeroCount);
        };
}

#endif // !SUDOKU_SOLVER_HPP