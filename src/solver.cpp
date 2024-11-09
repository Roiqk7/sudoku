/*
Date: 09/11/2024

Solver is class which given a sudoku grid, solves it Stochastic search / optimization methods.

Sources:
        [1] https://arxiv.org/pdf/0805.0697
*/

#include "../include/globals.hpp"
#include "../include/grid.hpp"
#include "../include/solver.hpp"
#include <array>

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
        Solves the grid using stochastic search / optimization methods.

        @param grid The grid to solve.
        */
        void Solver::solve(Grid& grid)
        {
                LOG_TRACE("Solver::solve() called");
                // TODO: Implement solve method
        }
// Stochastic search
        /*
        "The fitness function implemented here involves determining whether an
        integer is repeated or is not present in a particular row, column or
        grid. A fitness value is assigned to a possible solution based on the
        number of repeated or non-present integers. The more repeated or
        non-present integers there are in a solution’s rows and columns, the
        higher the fitness value assigned to that solution." [1]

        @param grid The grid to evaluate.

        @return The fitness of the grid.
        */
        int Solver::evalFitness(const Grid& grid) const noexcept
        {
                LOG_TRACE("Solver::evalFitness() called");

                int fitness = 0;

                for (int i = 0; i < grid.size()/9; i++)
                {
                        std::array<int, 9> row;
                        std::array<int, 9> col;
                        std::array<int, 9> box;

                        grid.getRow(i, row);
                        grid.getCol(i, col);
                        grid.getBox(i, box);

                        fitness += evalArrayFitness(row);
                        fitness += evalArrayFitness(col);
                        fitness += evalArrayFitness(box);

                }

                return fitness;
        }
// Stochastic helper methods
        /*
        Evaluates the fitness of an array.

        @param array The array to evaluate.

        @return The fitness of the array.

        @note The fitness is calculated as the number of repeated or non-present
        integers in the array. For more information, see [1].
        */
        int Solver::evalArrayFitness(const std::array<int, 9>& array) const noexcept
        {
                LOG_TRACE("Solver::evalArrayFitness() called");

                int fitness = 0;

                std::array<int, 9> occurences = {0};

                for (int i = 0; i < array.size(); i++)
                {
                        // If the value == 0, then it is not present in the array
                        if (array[i] == 0)
                        {
                                fitness++;
                        }
                        // Else, increment the occurence of the value
                        else
                        {
                                occurences[array[i] - 1]++;

                                // If the value is repeated, increment the fitness
                                if (occurences[array[i] - 1] > 1)
                                {
                                        fitness++;
                                }
                        }
                }

                return fitness;
        }
}