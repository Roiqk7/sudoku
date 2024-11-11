/*
Date: 10/11/2024

Generator is class which generates a new sudoku grid.
*/

#include "../include/generator.hpp"
#include "../include/macros.hpp"
#include "../include/grid.hpp"
#include "../include/solver.hpp"
#include <algorithm>
#include <array>
#include <random>

namespace Sudoku
{
// Class methods
        /*
        Constructor for the Generator class.
        */
        Generator::Generator()
        {
                LOG_TRACE("Generator::Generator() called");
        }

        /*
        Destructor for the Generator class.
        */
        Generator::~Generator()
        {
                LOG_TRACE("Generator::~Generator() called");
        }
// Generator methods
        /*
        Generates a new, filled sudoku grid.

        @param grid The grid to generate.
        */
        void Generator::generate(Grid& grid)
        {
                LOG_TRACE("Generator::generate() called");

                // Clear the grid
                grid.clear();

                Solver solver;
                // This ensures that the grid is validly filled
                do
                {
                        // Fill the diagonal boxes with random numbers
                        Generator::randomlyFillDiagonalBoxes(grid);
                }
                while (!solver.solve(grid));
        }

        /*
        Fills the diagonal boxes of the grid with random numbers.

        @param grid The grid to fill.
        */
        void Generator::randomlyFillDiagonalBoxes(Grid& grid)
        {
                LOG_TRACE("Generator::randomlyFillDiagonalBoxes() called");

                std::array<int, 9> boxArray;
                std::array<int, 9> values = {1, 2, 3, 4, 5, 6, 7, 8, 9};

                // Fill the diagonal boxes
                for (int i = 0; i < 3; i++)
                {
                        // Shuffle the values
                        std::shuffle(values.begin(), values.end(),
                                std::mt19937(std::random_device()()));

                        // Copy the values to the box array
                        boxArray = values;

                        // Set the box
                        grid.setBox(i * 4, boxArray);
                }
        }

} // namespace Sudoku