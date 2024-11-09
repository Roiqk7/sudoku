/*
Date: 09/11/2024

Solver is class which given a sudoku grid, solves it Stochastic search / optimization methods.
*/

#ifndef SUDOKU_SOLVER_HPP
#define SUDOKU_SOLVER_HPP

#include "grid.hpp"

namespace Sudoku
{
        class Solver
        {
        public: // Methods
        // Class methods
                Solver();
                ~Solver();
        // Solver methods
                void solve(Grid& grid);
        // Stochastic search
                int evalFitness(const Grid& grid) const noexcept;
        // Stochastic helper methods
                int evalArrayFitness(const std::array<int, 9>& array) const noexcept;

        };
}

#endif // !SUDOKU_SOLVER_HPP