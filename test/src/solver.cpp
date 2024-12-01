/*
Date: 10/11/2024

This file provides a few tests for the Solver class.
*/

#ifndef TEST
#error "Tried to compile a test file without the TEST macro defined. Aborting compilation."
#else

#include "../grid.hpp"
#include "../solver.hpp"
#include <array>
#include <gtest/gtest.h>

/*
Test for the Solver::solve() method.

Expected: No exceptions are thrown and the grid is solved.
*/
TEST(Solver, Solve)
{
        Sudoku::Grid grid;
        Sudoku::Solver solver;

        std::array<int, 9> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        grid.setBox(0, arr);
        grid.setBox(4, arr);
        grid.setBox(8, arr);

        ASSERT_TRUE(solver.solve(grid));
        ASSERT_TRUE(grid.isSolved());
}

#endif // !TEST