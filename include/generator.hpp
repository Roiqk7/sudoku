/*
Date: 10/11/2024

Generator is class which generates a new sudoku grid.
*/

#ifndef SUDOKU_GENERATOR_HPP
#define SUDOKU_GENERATOR_HPP

#include "grid.hpp"
#include "solver.hpp"

namespace Sudoku
{
        class Generator
        {
        public: // Methods
        // Class methods
                Generator();
                ~Generator();
        // Generator methods
                void generate(Grid& grid);
        private: // Methods
        // Generator methods
                void randomlyFillDiagonalBoxes(Grid& grid);
        };
}

#endif // !SUDOKU_GENERATOR_HPP