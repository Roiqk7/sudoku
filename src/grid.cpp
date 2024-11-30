/*
Date: 09/11/2024

This file implements the Grid class.
*/

#include "../include/macros.hpp"
#include "../include/grid.hpp"
#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include <stdexcept>

namespace Sudoku
{
// Class methods
        /*
        Constructor for the Grid class. Initializes the grid with zeros.
        */
        Grid::Grid()
        {
                LOG_TRACE("Grid::Grid() called");

                Grid::fill(0);
        }

        /*
        Destructor for the Grid class.
        */
        Grid::~Grid()
        {
                LOG_TRACE("Grid::~Grid() called");
        }
// Getters
        /*
        Returns the value of the cell at index i.

        @param i The index of the cell. Must be in the range [0, 80].

        @return The value of the cell at index i.

        @throw std::out_of_range if i is not in the index range.
        */
        int Grid::getCell(size_t i) const
        {
                LOG_TRACE("Grid::getCell() called");

                if (!checkCellIndex(i))
                {
                        LOG_ERROR("Index out of range");
                        throw std::out_of_range("Index out of range");
                }

                return grid[i];
        }

        /*
        Returns the value of the cell at row and col.

        @param row The row of the cell. Must be in the range [0, 8].
        @param col The column of the cell. Must be in the range [0, 8].

        @return The value of the cell at row and col.

        @throw std::out_of_range if row or col is not in the index range.
        */
        int Grid::getCell(size_t row, size_t col) const
        {
                LOG_TRACE("Grid::getCell() called");

                if (!checkCellIndex(row, col))
                {
                        LOG_ERROR("Index out of range");
                        throw std::out_of_range("Index out of range");
                }

                return grid[convertIndex(row, col)];
        }

        /*
        Returns the row at index row.

        @param row The row to get. Must be in the range [0, 8].
        @param rowArray The array to store the row in.

        @throw std::out_of_range if row is not in the index range.
        */
        void Grid::getRow(size_t row, std::array<int, 9>& rowArray) const
        {
                LOG_TRACE("Grid::getRow() called");

                if (!checkIndex(row))
                {
                        LOG_ERROR("Index out of range");
                        throw std::out_of_range("Index out of range");
                }

                for (int i = 0; i < 9; i++)
                {
                        rowArray[i] = grid[convertIndex(row, i)];
                }
        }

        /*
        Returns the column at index col.

        @param col The column to get. Must be in the range [0, 8].
        @param colArray The array to store the column in.

        @throw std::out_of_range if col is not in the index range.
        */
        void Grid::getCol(size_t col, std::array<int, 9>& colArray) const
        {
                LOG_TRACE("Grid::getCol() called");

                if (!checkIndex(col))
                {
                        LOG_ERROR("Index out of range");
                        throw std::out_of_range("Index out of range");
                }

                for (size_t i = 0; i < 9; i++)
                {
                        colArray[i] = grid[convertIndex(i, col)];
                }
        }

        /*
        Returns the box at index box.

        @param box The box to get. Must be in the range [0, 8].
        @param boxArray The array to store the box in.

        @throw std::out_of_range if box is not in the index range.
        */
        void Grid::getBox(size_t box, std::array<int, 9>& boxArray) const
        {
                LOG_TRACE("Grid::getBox() called");

                if (!checkIndex(box))
                {
                        LOG_ERROR("Index out of range");
                        throw std::out_of_range("Index out of range");
                }

                size_t rowStartIndex = (box / 3) * 27 + (box % 3) * 3;

                for (size_t i = 0; i < 3; ++i)
                {
                        for (size_t j = 0; j < 3; ++j)
                        {
                                boxArray[i * 3 + j]
                                        = grid[rowStartIndex + j];
                        }
                        rowStartIndex += 9;
                }
        }
// Setters
        /*
        Sets count random cells to zero.

        @param count The number of cells to set to zero.

        @note This functions is smart and will try to interpret
                the count as best as it can.
        */
        void Grid::setZero(size_t count)
        {
                LOG_TRACE("Grid::setZero() called");

                // First, we find all non-zero cells by index
                std::vector<size_t> nonZeroCells;
                nonZeroCells.reserve(size());

                for (size_t i = 0; i < size(); ++i)
                {
                        if (grid[i] != 0)
                        {
                                nonZeroCells.push_back(i);
                        }
                }

                if (count >= nonZeroCells.size())
                {
                        grid.fill(0);
                }
                else
                {
                        std::shuffle(nonZeroCells.begin(), nonZeroCells.end(),
                                std::mt19937{std::random_device{}()});

                        for (size_t i = 0; i < count; i++)
                        {
                                grid[nonZeroCells[i]] = 0;
                        }
                }
        }

        /*
        Sets the value of the cell at index i.

        @param i The index of the cell. Must be in the range [0, 80].
        @param value The value to set the cell to.

        @throw std::out_of_range if i is not in the index range.
        */
        void Grid::setCell(size_t i, int value)
        {
                LOG_TRACE("Grid::setCell() called");

                if (!checkCellIndex(i))
                {
                        LOG_ERROR("Index out of range");
                        throw std::out_of_range("Index out of range");
                }

                grid[i] = value;
        }

        /*
        Sets the row at index row.

        @param row The row to set. Must be in the range [0, 8].
        @param rowArray The array to set the row to.

        @throw std::out_of_range if row is not in the index range.
        */
        void Grid::setRow(size_t row, const std::array<int, 9>& rowArray)
        {
                LOG_TRACE("Grid::setRow() called");

                if (!checkIndex(row))
                {
                        LOG_ERROR("Index out of range");
                        throw std::out_of_range("Index out of range");
                }

                for (size_t i = 0; i < 9; i++)
                {
                        grid[convertIndex(row, i)] = rowArray[i];
                }
        }

        /*
        Sets the column at index col.

        @param col The column to set. Must be in the range [0, 8].
        @param colArray The array to set the column to.

        @throw std::out_of_range if col is not in the index range.
        */
        void Grid::setCol(size_t col, const std::array<int, 9>& colArray)
        {
                LOG_TRACE("Grid::setCol() called");

                if (!checkIndex(col))
                {
                        LOG_ERROR("Index out of range");
                        throw std::out_of_range("Index out of range");
                }

                for (size_t i = 0; i < 9; i++)
                {
                        grid[convertIndex(i, col)] = colArray[i];
                }
        }

        /*
        Sets the box at index box.

        @param box The box to set. Must be in the range [0, 8].
        @param boxArray The array to set the box to.

        @throw std::out_of_range if box is not in the index range.
        */
        void Grid::setBox(size_t box, const std::array<int, 9>& boxArray)
        {
                LOG_TRACE("Grid::setBox() called");

                if (!checkIndex(box))
                {
                        LOG_ERROR("Index out of range");
                        throw std::out_of_range("Index out of range");
                }

                size_t rowStartIndex = (box / 3) * 27 + (box % 3) * 3;

                for (size_t i = 0; i < 3; ++i)
                {
                        for (size_t j = 0; j < 3; ++j)
                        {
                                grid[rowStartIndex + j] = boxArray[i * 3 + j];
                        }
                        rowStartIndex += 9;
                }
        }
// Utility
        /*
        Returns the size of the grid.

        @return The size of the grid.
        */
        size_t Grid::size() const noexcept
        {
                LOG_TRACE("Grid::size() called");

                return grid.size();
        }

        /*
        Clears the grid.
        */
        void Grid::clear() noexcept
        {
                LOG_TRACE("Grid::clear() called");

                grid.fill(0);
        }

        /*
        Fills the grid with a value.

        @param value The value to fill the grid with. Default is 0.
        */
        void Grid::fill(int value)
        {
                LOG_TRACE("Grid::fill() called");

                grid.fill(value);
        }

        /*
        Converts a row and column index to a 1D index.

        @param row The row index. Must be in the range [0, 8].
        @param col The column index. Must be in the range [0, 8].

        @return The 1D index.

        @throw std::out_of_range if row or col is not in the index range.
        */
        size_t Grid::convertIndex(size_t row, size_t col) const
        {
                LOG_TRACE("Grid::convertIndex() called");

                if (!checkCellIndex(row, col))
                {
                        LOG_ERROR("Index out of range");
                        throw std::out_of_range("Index out of range");
                }

                return row * 9 + col;
        }

        /*
        Prints the grid to the console.
        */
        void Grid::print() const noexcept
        {
                LOG_TRACE("Grid::print() called");
                for (int i = 0; i < 9; i++)
                {
                        for (int j = 0; j < 9; j++)
                        {
                                std::cout << grid[Grid::convertIndex(i, j)] << " ";
                                if (j == 2 || j == 5)
                                {
                                        std::cout << "| ";
                                }
                        }
                        std::cout << std::endl;
                        if (i == 2 || i == 5)
                        {
                                std::cout << "------|-------|------" << std::endl;
                        }
                }
        }

        /*
        Counts the number of times a value appears in the grid.

        @param value The value to count.

        @return The number of times the value appears in the grid.
        */
        int Grid::count(int value) const
        {
                LOG_TRACE("Grid::count() called");

                return std::count(grid.begin(), grid.end(), value);
        }
// Checkers
        /*
        Checks if the grid is solved.

        @return True if the grid is solved, false otherwise.

        @note A grid is considered solved if it has no zeros and every
                row, column, and box contains all the numbers 1-9.
        */
        bool Grid::isSolved() const noexcept
        {
                LOG_TRACE("Grid::isSolved() called");

                // Note: The zero check is not necessary as the areValidValues()
                // function will return false if any zero is found.
                for (size_t i = 0; i < 9; i++)
                {
                        std::array<int, 9> arr;

                        getRow(i, arr);
                        if (!areValidValues(arr))
                        {
                                return false;
                        }

                        getCol(i, arr);
                        if (!areValidValues(arr))
                        {
                                return false;
                        }

                        getBox(i, arr);
                        if (!areValidValues(arr))
                        {
                                return false;
                        }
                }

                return true;
        }

        /*
        Checks if the grid contains a value.

        @param value The value to check for.

        @return True if the grid contains the value, false otherwise.
        */
        bool Grid::contains(int value) const noexcept
        {
                LOG_TRACE("Grid::contains() called");

                return std::find(grid.begin(), grid.end(), value) != grid.end();
        }

        /*
        Checks if an array of values are valid.

        @param array The array of values to check.

        @return True if the array is valid, false otherwise.

        @note An array is considered valid if every number is in the range [1, 9].
        */
        bool Grid::areValidValues(const std::array<int, 9>& array) const noexcept
        {
                LOG_TRACE("Grid::areValidValues() called");

                std::bitset<9> values;

                for (size_t i = 0; i < 9; i++)
                {
                        values[array[i] - 1] = true;
                }

                return values.all();
        }

        /*
        Checks if a value can be set at index i.

        @param i The index to check.
        @param value The value to set.

        @return True if the value can be set, false otherwise.

        @throw std::out_of_range if i is not in the index range.

        @note A value can be set if placing it would not violate the rules of sudoku.
        */
        bool Grid::isValidValueToSet(size_t i, int value)
        {
                LOG_TRACE("Grid::isValidValueToSet() called");

                // We place the value at the index and check if the grid is still valid
                int originalValue = grid[i];
                setCell(i, value);

                // Check if the grid is still valid
                size_t row = i / 9;
                size_t col = i % 9;
                std::array<int, 9> arr;

                getRow(row, arr);
                if (!areValidValues(arr))
                {
                        setCell(i, originalValue);
                        return false;
                }

                getCol(col, arr);
                if (!areValidValues(arr))
                {
                        setCell(i, originalValue);
                        return false;
                }

                size_t box = (row / 3) * 3 + (col / 3);
                getBox(box, arr);
                if (!areValidValues(arr))
                {
                        setCell(i, originalValue);
                        return false;
                }

                // Reset the cell to its original value
                setCell(i, originalValue);

                return true;
        }

// Utility checkers
        /*
        Checks if the cell index is valid.

        @param i The index of the cell.

        @return True if the index is valid, false otherwise.

        @note The index is considered valid if it is in the range [0, 80].
        */
        bool Grid::checkCellIndex(size_t i) const noexcept
        {
                LOG_TRACE("Grid::checkCellIndex() called");

                return i < size();
        }

        /*
        Checks if the cell index is valid.

        @param row The row of the cell.
        @param col The column of the cell.

        @return True if the index is valid, false otherwise.

        @note The index is considered valid if both the row and column are in the range [0, 8].
        */
        bool Grid::checkCellIndex(size_t row, size_t col) const noexcept
        {
                LOG_TRACE("Grid::checkCellIndex() called");

                return checkIndex(row) && checkIndex(col);
        }

        /*
        Checks if the index is valid.

        @param i The index to check.

        @return True if the index is valid, false otherwise.

        @note The index is considered valid if it is in the range [0, 8].
        */
        bool Grid::checkIndex(size_t i) const noexcept
        {
                LOG_TRACE("Grid::checkIndex() called");

                return i < 9;
        }

} // namespace Sudoku