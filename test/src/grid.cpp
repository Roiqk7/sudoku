/*
Date: 09/11/2024

This file provides a few tests for the Grid class.
*/

#ifndef TEST
#error "Tried to compile a test file without the TEST macro defined. Aborting compilation."
#else

#include "../grid.hpp"
#include <array>
#include <gtest/gtest.h>

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

Expected: Some exceptions are thrown.
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

        // Exceptions are thrown
        ASSERT_THROW(grid.setCell(-1, 0, val), std::out_of_range);
        ASSERT_THROW(grid.setCell(0, -1, val), std::out_of_range);
        ASSERT_THROW(grid.setCell(9, 0, val), std::out_of_range);
        ASSERT_THROW(grid.setCell(0, 9, val), std::out_of_range);
}

/*
Test for the Grid getters.

Expected: Some exceptions are thrown and all methods return the expected values.
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

        // Exceptions are thrown
        ASSERT_THROW(grid.getRow(-1, rowArray), std::out_of_range);
        ASSERT_THROW(grid.getRow(9, rowArray), std::out_of_range);
        ASSERT_THROW(grid.getCol(-1, colArray), std::out_of_range);
        ASSERT_THROW(grid.getCol(9, colArray), std::out_of_range);
        ASSERT_THROW(grid.getBox(-1, boxArray), std::out_of_range);
        ASSERT_THROW(grid.getBox(9, boxArray), std::out_of_range);
}

/*
Test for the Grid index related methods.

Expected: Some exceptions are thrown and all methods return the expected values.
*/
TEST(Grid, Index)
{
        Sudoku::Grid grid;

        // convertIndex()
        // No exceptions are thrown
        ASSERT_EQ(grid.convertIndex(0, 0), 0);
        ASSERT_EQ(grid.convertIndex(4, 4), 40);
        ASSERT_EQ(grid.convertIndex(2, 4), 22);
        ASSERT_EQ(grid.convertIndex(8, 8), 80);

        // Exceptions are thrown
        ASSERT_THROW(grid.convertIndex(-1, 0), std::out_of_range);
        ASSERT_THROW(grid.convertIndex(0, -1), std::out_of_range);
        ASSERT_THROW(grid.convertIndex(9, 0), std::out_of_range);
        ASSERT_THROW(grid.convertIndex(0, 9), std::out_of_range);

        // checkIndex()
        ASSERT_TRUE(grid.checkIndex(0, true));
        ASSERT_TRUE(grid.checkIndex(80, true));
        ASSERT_TRUE(grid.checkIndex(1, false));

        ASSERT_FALSE(grid.checkIndex(-1, true));
        ASSERT_FALSE(grid.checkIndex(81, true));
        ASSERT_FALSE(grid.checkIndex(-1, true));
        ASSERT_FALSE(grid.checkIndex(9, false));
}

/*
Test for check methods.

Expected: No exceptions are thrown and all methods return the expected values.
*/
TEST(Grid, Check)
{
        Sudoku::Grid grid;
        std::array<int, 9> setter = {1, 2, 3, 4, 5, 6, 7, 8, 9};

        grid.setRow(0, setter);
        grid.setCol(0, setter);
        grid.setBox(0, setter);

        // True
        ASSERT_TRUE(grid.isValidCell(0, 0));
        ASSERT_TRUE(grid.isValidRow(0));
        ASSERT_TRUE(grid.isValidCol(0));
        ASSERT_TRUE(grid.isValidBox(0));
        ASSERT_TRUE(grid.isValid());

        // False
        grid.setCell(0, 0, -1);
        ASSERT_FALSE(grid.isSolved());
        ASSERT_FALSE(grid.isValidCell(0, 0));
        ASSERT_FALSE(grid.isValidRow(0));
        ASSERT_FALSE(grid.isValidCol(0));
        ASSERT_FALSE(grid.isValidBox(0));
        ASSERT_FALSE(grid.isValid());
}

#endif // !TEST