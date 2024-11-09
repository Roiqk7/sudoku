/*
Date: 09/11/2024

Solver is class which given a sudoku grid, solves it Stochastic search / optimization methods.

Sources:
        [1] https://arxiv.org/pdf/0805.0697
*/

#include "../include/globals.hpp"
#include "../include/grid.hpp"
#include "../include/solver.hpp"
#include <algorithm>
#include <array>
#include <random>
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
        4.4. CGA Applied to the Sudoku Problem: Second Approach [1]

        @param grid The grid to solve.

        @note Missing numbers are represented by zeros and the fixed numbers
        are assumed to be correct.
        */
        void Solver::solve(Grid& grid)
        {
                LOG_TRACE("Solver::solve() called");

                // Initialize the population
                std::vector<Grid> population(100, grid);
                initializePopulation(population);

                // Search for the solution
                int maxFitness;
                size_t fittestIndex;
                do
                {
                        // Evaluate the fitness of the population
                        for (size_t i = 0; i < population.size(); i++)
                        {
                                int fitness = evalFitness(population[i]);
                                if (fitness > maxFitness)
                                {
                                        maxFitness = fitness;
                                        fittestIndex = i;
                                }
                        }

                        // Mutation
                        mutation(population, maxFitness);
                }
                while (maxFitness != 0);

                // Set the grid to the solution
                grid = population[fittestIndex];
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
                        // std::array<int, 9> box;

                        grid.getRow(i, row);
                        grid.getCol(i, col);
                        // grid.getBox(i, box);

                        fitness += evalArrayFitness(row);
                        fitness += evalArrayFitness(col);
                        // fitness += evalArrayFitness(box);

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

        /*
        "This approach uses the third solution space representation scheme
        mentioned in Section 2. Each individual is represented as a completed
        puzzle where the third constraint mentioned in Section 1 is met: each 3x3
        grid in each puzzle contains the numbers 1 to 9 exactly once. Each 3x3
        grid is thus considered a gene." [1]

        @param population The population to initialize.
        */
        void Solver::initializePopulation(std::vector<Grid>& population) const
        {
                // TODO: Parallelize this function (using 4 threads one for 25 grids)

                LOG_TRACE("Solver::initializePopulation() called");

                for (auto& grid : population)
                {
                        // We fill the remaining cells so that each 3x3 grid
                        // contains the numbers 1 to 9 exactly once. We respect
                        // the initial values of the grid.

                        // For each box
                        std::vector<int> missingValues;
                        for (int i = 0; i < 9; i++)
                        {
                                std::array<int, 9> box;
                                grid.getBox(i, box);

                                // Find the missing values
                                for (int j = 1; j <= 9; j++)
                                {
                                        if (std::find(box.begin(), box.end(), j) == box.end())
                                        {
                                                missingValues.push_back(j);
                                        }
                                }

                                // Shuffle the missing values
                                std::random_device rd;
                                std::mt19937 g(rd());
                                std::shuffle(missingValues.begin(), missingValues.end(), g);

                                // Fill the box with the missing values
                                for (int j = 0; j < 9; j++)
                                {
                                        if (box[j] == 0)
                                        {
                                                grid.setCell(i, j, missingValues.back());
                                                missingValues.pop_back();
                                        }
                                }
                        }
                }
        }
}