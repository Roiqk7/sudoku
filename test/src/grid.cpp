/*
Date: 09/11/2024

This file provides a few tests for the Grid class.
*/

#ifndef TEST
#error "Tried to compile a test file without the TEST macro defined. Aborting compilation."
#else

#include "../../include/grid.hpp"
#include <array>
#include <gtest/gtest.h>
#include <iostream>

/*
Test for the Grid::Grid() constructor.

Expected: No exceptions are thrown.
*/
TEST(Grid, Constructor)
{
        Sudoku::Grid grid;
}

/*
Test for the Grid setters.

Expected: No exceptions are thrown.
*/
TEST(Grid, Setters)
{
        Sudoku::Grid grid;
        int val = 1;
        std::array<int, 9> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9};

        grid.setCell(0, 0, 1);
        grid.setCell(0, 0, val);
        grid.setRow(0, arr);
        grid.setCol(0, arr);
        grid.setBox(0, arr);
}

/*
Test for the Grid getters.

Expected: No exceptions are thrown and all methods return the expected values.
*/
TEST(Grid, Getters)
{
        Sudoku::Grid grid;
        std::array<int, 9> setter = {1, 2, 3, 4, 5, 6, 7, 8, 9};

        grid.setRow(0, setter);
        grid.setCol(0, setter);
        grid.setBox(0, setter);

        std::array<int, 9> rowArray;
        std::array<int, 9> colArray;
        std::array<int, 9> boxArray;

        grid.getCell(0, 0);
        grid.getRow(0, rowArray);
        grid.getCol(0, colArray);
        grid.getBox(0, boxArray);

        ASSERT_EQ(rowArray, setter);
        ASSERT_EQ(colArray, setter);
        ASSERT_EQ(boxArray, setter);
}

/*
Test for the Grid::clear() method.

#endif // !TEST