/*
Date: 10/11/2024

This file provides a few tests for the Generator class.
*/

#ifndef TEST
#error "Tried to compile a test file without the TEST macro defined. Aborting compilation."
#else

#include "../../include/generator.hpp"
#include "../../include/grid.hpp"
#include <array>
#include <gtest/gtest.h>

/*
Test for the Generator::generate() method.

Expected: No exceptions are thrown and no zeros are present in the grid.
*/
TEST(Generator, Generate)
{
        Sudoku::Grid grid;
        Sudoku::Generator generator;

        generator.generate(grid);

        ASSERT_TRUE(grid.count(0) == 0);
        ASSERT_TRUE(grid.isSolved());
}

#endif // !TEST