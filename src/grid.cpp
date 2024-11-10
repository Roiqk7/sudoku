/*
Date: 09/11/2024

This file implements the Grid class.
*/

#include "../include/globals.hpp"
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
// Getter methods
        /*
        Returns the value of the cell at the specified index.

        @param i The index of the cell. Must be in the range [0, 80].

        @return The value of the cell at the specified index.

        @throw std::out_of_range if i is out of range.
        */
        int Grid::getCell(int i) const
        {
                LOG_TRACE("Grid::getCell() called");
                if (!Grid::checkIndex(i, true))
                {
                        LOG_ERROR("Index out of range");
                        throw std::out_of_range("Index out of range");
                }
                return grid[i];
        }

        /*
        Returns the value of the cell at the specified row and column.

        @param row The row of the cell. Must be in the range [0, 9].
        @param col The column of the cell. Must be in the range [0, 9].

        @return The value of the cell at the specified row and column.

        @throw std::out_of_range if row or col is out of range.
        */
        int Grid::getCell(int row, int col) const
        {
                LOG_TRACE("Grid::getCell() called");
                const int index = Grid::convertIndex(row, col);
                return grid[Grid::convertIndex(row, col)];
        }

        /*
        Returns the values of the cells in the specified row.

        @param row The row to get. Must be in the range [0, 9].
        @param rowArray The array to store the values of the cells in the row.

        @throw std::out_of_range if row is out of range.
        */
        void Grid::getRow(int row, std::array<int, 9>& rowArray) const
        {
                LOG_TRACE("Grid::getRow() called");
                if (!Grid::checkIndex(row, false))
                {
                        LOG_ERROR("Row out of range");
                        throw std::out_of_range("Row out of range");
                }
                for (int i = 0; i < 9; i++)
                {
                        rowArray[i] = grid[Grid::convertIndex(row, i)];
                }
        }

        /*
        Returns the values of the cells in the specified column.

        @param col The column to get. Must be in the range [0, 9].
        @param colArray The array to store the values of the cells in the column.

        @throw std::out_of_range if col is out of range.
        */
        void Grid::getCol(int col, std::array<int, 9>& colArray) const
        {
                LOG_TRACE("Grid::getCol() called");
                if (!Grid::checkIndex(col, false))
                {
                        LOG_ERROR("Column out of range");
                        throw std::out_of_range("Column out of range");
                }
                for (int i = 0; i < 9; i++)
                {
                        colArray[i] = grid[Grid::convertIndex(i, col)];
                }
        }

        /*
        Returns the values of the cells in the specified box.

        @param box The box to get. Must be in the range [0, 9].
        @param boxArray The array to store the values of the cells in the box.

        @throw std::out_of_range if box is out of range.
        */
        void Grid::getBox(int box, std::array<int, 9>& boxArray) const
        {
                LOG_TRACE("Grid::getBox() called");
                if (!Grid::checkIndex(box, false))
                {
                        LOG_ERROR("Box out of range");
                        throw std::out_of_range("Box out of range");
                }
                const std::array<int, 9>
                        startIndex = {0, 3, 6, 27, 30, 33, 54, 57, 60};         // The starting index of each box
                int rowStartIndex = startIndex[box];
                for (int i = 0; i < 3; i++)
                {
                        for (int j = rowStartIndex; j <= rowStartIndex + 2; j++)
                        {
                                boxArray[i * 3 + j - rowStartIndex] = grid[j];
                        }
                        rowStartIndex += 9;
                }
        }

        /*
        Returns the fixed values of the cells in the specified box.

        @param box The box to get. Must be in the range [0, 9].
        @param boxArray The array to store the values of the cells in the box.

        @throw std::out_of_range if box is out of range.
        */
        void Grid::getBoxFixed(int box, std::array<bool, 9>& boxArray) const
        {
                LOG_TRACE("Grid::getBoxFixed() called");

                if (!Grid::checkIndex(box, false))
                {
                        LOG_ERROR("Box out of range");
                        throw std::out_of_range("Box out of range");
                }
                const std::array<int, 9>
                        startIndex = {0, 3, 6, 27, 30, 33, 54, 57, 60};         // The starting index of each box
                int rowStartIndex = startIndex[box];
                for (int i = 0; i < 3; i++)
                {
                        for (int j = rowStartIndex; j <= rowStartIndex + 2; j++)
                        {
                                boxArray[i * 3 + j - rowStartIndex] = fixed[j];
                        }
                        rowStartIndex += 9;
                }
        }
// Setter methods
        /*
        Sets the values of the cells in the grid to zero.

        @param count The number of cells to set to zero.
        */
        void Grid::setZero(int count) noexcept
        {
                LOG_TRACE("Grid::setZero() called");

                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<int> dis(0, 80);
                int index;

                for (int i = 0; i < count; i++)
                {
                        do
                        {
                                index = dis(gen);
                        }
                        while (grid[index] == 0);
                        grid[index] = 0;
                }
        }

        /*
        Sets the value of the cell at the specified index.

        @param i The index of the cell. Must be in the range [0, 80].
        @param value The value to set the cell to. Must be in the range [0, 9].

        @throw std::out_of_range if i is out of range.
        @throw std::invalid_argument if value is out of range.
        */
        void Grid::setCell(int i, int value)
        {
                LOG_TRACE("Grid::setCell() called");
                if (!Grid::checkIndex(i, true))
                {
                        LOG_ERROR("Index out of range");
                        throw std::out_of_range("Index out of range");
                }
                if (value < 0 || value > 9)
                {
                        LOG_ERROR("Value out of range");
                        throw std::invalid_argument("Value out of range");
                }
                grid[i] = value;
        }

        /*
        Sets the value of the cell at the specified row and column.

        @param row The row of the cell. Must be in the range [0, 9].
        @param col The column of the cell. Must be in the range [0, 9].
        @param value The value to set the cell to. Must be in the range [0, 9].

        @throw std::out_of_range if row or col is out of range.
        @throw std::invalid_argument if value is out of range.
        */
        void Grid::setCell(int row, int col, int value)
        {
                LOG_TRACE("Grid::setCell() called");
                const int index = Grid::convertIndex(row, col);
                if (value < 0 || value > 9)
                {
                        LOG_ERROR("Value out of range");
                        throw std::invalid_argument("Value out of range");
                }
                grid[index] = value;
        }

        /*
        Sets the values of the cells in the specified row.

        @param row The row to set. Must be in the range [0, 9].
        @param rowArray The array containing the values to set the cells in the row to.

        @throw std::out_of_range if row is out of range.
        */
        void Grid::setRow(int row, const std::array<int, 9>& rowArray)
        {
                LOG_TRACE("Grid::setRow() called");
                if (!Grid::checkIndex(row, false))
                {
                        LOG_ERROR("Row out of range");
                        throw std::out_of_range("Row out of range");
                }
                for (int i = 0; i < 9; i++)
                {
                        grid[Grid::convertIndex(row, i)] = rowArray[i];
                }
        }

        /*
        Sets the values of the cells in the specified column.

        @param col The column to set. Must be in the range [0, 9].
        @param colArray The array containing the values to set the cells in the column to.

        @throw std::out_of_range if col is out of range.
        */
        void Grid::setCol(int col, const std::array<int, 9>& colArray)
        {
                LOG_TRACE("Grid::setCol() called");
                if (!Grid::checkIndex(col, false))
                {
                        LOG_ERROR("Column out of range");
                        throw std::out_of_range("Column out of range");
                }
                for (int i = 0; i < 9; i++)
                {
                        grid[Grid::convertIndex(i, col)] = colArray[i];
                }
        }

        /*
        Sets the values of the cells in the specified box.

        @param box The box to set. Must be in the range [0, 9].
        @param boxArray The array containing the values to set the cells in the box to.

        @throw std::out_of_range if box is out of range.
        */
        void Grid::setBox(int box, const std::array<int, 9>& boxArray)
        {
                LOG_TRACE("Grid::setBox() called");
                if (!Grid::checkIndex(box, false))
                {
                        LOG_ERROR("Box out of range");
                        throw std::out_of_range("Box out of range");
                }
                const std::array<int, 9>
                        startIndex = {0, 3, 6, 27, 30, 33, 54, 57, 60};         // The starting index of each box
                int rowStartIndex = startIndex[box];
                for (int i = 0; i < 3; i++)
                {
                        for (int j = rowStartIndex; j <= rowStartIndex + 2; j++)
                        {
                                grid[j] = boxArray[i * 3 + j - rowStartIndex];
                        }
                        rowStartIndex += 9;
                }
        }
// Utility methods
        /*
        Returns the size of the grid.

        @return The size of the grid.

        @note The size of the grid is 81.
        */
        size_t Grid::size() const noexcept
        {
                LOG_TRACE("Grid::size() called");
                return grid.size();
        }

        /*
        Clears the grid by setting all cells to zero.
        */
        void Grid::clear() noexcept
        {
                LOG_TRACE("Grid::clear() called");
                Grid::fill(0);
        }

        /*
        Fills the grid with the specified value.

        @param value The value to fill the grid with.
        */
        void Grid::fill(int value) noexcept
        {
                LOG_TRACE("Grid::fill() called");
                for (int i = 0; i < 81; i++)
                {
                        grid[i] = value;
                }
        }

        /*
        Converts the row and column to an index in the grid array.

        @param row The row of the cell. Must be in the range [0, 9].
        @param col The column of the cell. Must be in the range [0, 9].

        @return The index in the grid array corresponding to the row and column.

        @throw std::out_of_range if row or col is out of range.
        */
        int Grid::convertIndex(int row, int col) const
        {
                LOG_TRACE("Grid::convertIndex() called");
                if (!Grid::checkIndex(row, false) || !Grid::checkIndex(col, false))
                {
                        LOG_ERROR("Row or column out of range");
                        throw std::out_of_range("Row or column out of range");
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
        Counts the number of occurrences of the specified value in the grid.

        @param value The value to count.

        @return The number of occurrences of the value in the grid.
        */
        int Grid::count(int value) const noexcept
        {
                LOG_TRACE("Grid::count() called");
                return std::count(grid.begin(), grid.end(), value);
        }
// Check methods
        /*
        Checks if the index is valid.

        @param index The index to check.
        @param cell True if the index is for a cell, false if it is for a row, column, or box.

        @return True if the index is valid, false otherwise.
        */
        bool Grid::checkIndex(int index, bool cell) const noexcept
        {
                LOG_TRACE("Grid::checkIndex() called");
                if (cell)
                {
                        return 0 <= index && index < 81;
                }
                return 0 <= index && index < 9;
        }

        /*
        Checks if the grid is solved.

        @return True if the grid is solved, false otherwise.
        */
        bool Grid::isSolved() const noexcept
        {
                LOG_TRACE("Grid::isSolved() called");
                // Grid is solved if it is valid and has no zeros
                return Grid::isValid() && std::none_of(grid.begin(), grid.end(), [](int value)
                {
                        return value == 0;
                });
        }

        /*
        Checks if the value is valid for the cell at the specified row and column.

        @param row The row of the cell. Must be in the range [0, 9].
        @param col The column of the cell. Must be in the range [0, 9].
        @param value The value to check.

        @return True if the value is valid for the cell, false otherwise.

        @throw std::out_of_range if row or col is out of range.

        @note A valid value is in the range (0, 9] and does not conflict with the row, column, or box.
        */
        bool Grid::isValidValue(int row, int col, int value) const noexcept
        {
                LOG_TRACE("Grid::isValidValue() called");
                if (value <= 0 || value > 9)
                {
                        return false;
                }

                std::array<int, 9> rowArray;
                std::array<int, 9> colArray;
                std::array<int, 9> boxArray;
                Grid::getRow(row, rowArray);
                Grid::getCol(col, colArray);
                Grid::getBox(row / 3 * 3 + col / 3, boxArray);

                return std::none_of(rowArray.begin(), rowArray.end(), [value](int val)
                {
                        return val == value;
                })
                &&
                std::none_of(colArray.begin(), colArray.end(), [value](int val)
                {
                        return val == value;
                })
                &&
                std::none_of(boxArray.begin(), boxArray.end(), [value](int val)
                {
                        return val == value;
                });
        }

        /*
        Checks if the value of the cell at the specified row and column is valid.

        @param row The row of the cell. Must be in the range [0, 9].
        @param col The column of the cell. Must be in the range [0, 9].
        @param includeZero True if zero is considered a valid value, false otherwise.

        @return True if the value of the cell is valid, false otherwise.

        @throw std::out_of_range if row or col is out of range.

        @note A valid cell has a value in the range [0, 9].
        */
        bool Grid::isValidCell(int row, int col, bool includeZero) const noexcept
        {
                LOG_TRACE("Grid::isValidCell() called");
                const int value = grid[Grid::convertIndex(row, col)];
                return 0 <= value && value <= 9;
        }

        /*
        Checks if the values in the specified row are valid.

        @param row The row to check. Must be in the range [0, 9].

        @return True if the values in the row are valid, false otherwise.

        @throw std::out_of_range if row is out of range.

        @note A valid row has values in the range [0, 9].
        */
        bool Grid::isValidRow(int row) const noexcept
        {
                LOG_TRACE("Grid::isValidRow() called");
                std::array<int, 9> rowArray;
                Grid::getRow(row, rowArray);
                return std::all_of(rowArray.begin(), rowArray.end(), [this, row](int value)
                {
                        return Grid::isValidCell(row, value, true);
                });
        }

        /*
        Checks if the values in the specified column are valid.

        @param col The column to check. Must be in the range [0, 9].

        @return True if the values in the column are valid, false otherwise.

        @throw std::out_of_range if col is out of range.

        @note A valid column has values in the range [0, 9].
        */
        bool Grid::isValidCol(int col) const noexcept
        {
                LOG_TRACE("Grid::isValidCol() called");
                std::array<int, 9> colArray;
                Grid::getCol(col, colArray);
                return std::all_of(colArray.begin(), colArray.end(), [this, col](int value)
                {
                        return Grid::isValidCell(value, col, true);
                });
        }

        /*
        Checks if the values in the specified box are valid.

        @param box The box to check. Must be in the range [0, 9].

        @return True if the values in the box are valid, false otherwise.

        @throw std::out_of_range if box is out of range.

        @note A valid box has values in the range [0, 9].
        */
        bool Grid::isValidBox(int box) const noexcept
        {
                LOG_TRACE("Grid::isValidBox() called");
                std::array<int, 9> boxArray;
                Grid::getBox(box, boxArray);
                return std::all_of(boxArray.begin(), boxArray.end(), [this, box](int value)
                {
                        return Grid::isValidCell(value, box, true);
                });
        }

        /*
        Checks if the grid is valid.

        @return True if the grid is valid, false otherwise.

        @note A valid grid has valid rows, columns, and boxes.
        */
        bool Grid::isValid() const noexcept
        {
                LOG_TRACE("Grid::isValid() called");
                const bool validRows = std::all_of(
                        std::begin(grid), std::end(grid), [this](int value)
                        {
                                return Grid::isValidRow(value);
                        });
                const bool validCols = std::all_of(
                        std::begin(grid), std::end(grid), [this](int value)
                        {
                                return Grid::isValidCol(value);
                        });
                const bool validBoxes = std::all_of(
                        std::begin(grid), std::end(grid), [this](int value)
                        {
                                return Grid::isValidBox(value);
                        });
                return validRows && validCols && validBoxes;
        }


} // namespace Sudoku